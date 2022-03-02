import unittest
import subprocess
import os
import sys


class SmokeTest(unittest.TestCase):
    def check(self, test_input, correct_answer):
        proc = subprocess.Popen(["./build/topsh"],
                                stdin=subprocess.PIPE,
                                stdout=subprocess.PIPE)
        out = proc.communicate(test_input.encode())[0].decode("UTF-8")

        self.assertEqual(out, correct_answer)
        self.assertEqual(proc.returncode, 0)

    def test_exit(self):
        self.check("exit", "")

    def test_echo(self):
        self.check("echo Hello", "Hello")

    def test_echo_with_space(self):
        self.check("echo Hello   ", "Hello")

    def test_echo_long(self):
        self.check("echo Hello Hello                      Hello", 
                   "Hello Hello Hello")

    def test_pwd(self):
        self.check("pwd", os.getcwd())

    def test_echo_after_exit(self):
        self.check("exit\necho Hello", "")

    def test_exit_after_exit(self):
        self.check("exit\nexit", "")

    def test_cat(self):
        with open("__test_file", "w") as f:
            f.write("1\n2\n3")
        self.check("cat __test_file", "1\n2\n3\n")
        os.remove("__test_file")

    def test_cat_twice(self):
        with open("__test_file", "w") as f:
            f.write("1\n2\n3")
        self.check("cat __test_file __test_file", "1\n2\n3\n1\n2\n3\n")
        os.remove("__test_file")

    def test_wc(self):
        with open("__test_file", "w") as f:
            f.write("1\n2\n3")
        self.check("wc __test_file", "3 3 6 __test_file\n")
        os.remove("__test_file")

    def test_wc_spaced(self):
        with open("__test_file", "w") as f:
            f.write("1\n2\n3")
        self.check("wc                                    __test_file", 
                   "3 3 6 __test_file\n")
        os.remove("__test_file")

    def test_wc_spaced_on_end(self):
        with open("__test_file", "w") as f:
            f.write("1\n2\n3")
        self.check("wc                __test_file   ", 
                   "3 3 6 __test_file\n")
        os.remove("__test_file")

    def test_wc_twice(self):
        with open("__test_file", "w") as f:
            f.write("1\n2\n3")
        self.check("wc __test_file __test_file",
                   "3 3 6 __test_file\n3 3 6 __test_file\n6 6 12 total\n")
        os.remove("__test_file")

    def test_cat_with_endline(self):
        with open("__test_file", "w") as f:
            f.write("1\n2\n3\n")
        self.check("cat __test_file", "1\n2\n3\n\n")
        os.remove("__test_file")

    def test_cat_with_endline_twice(self):
        with open("__test_file", "w") as f:
            f.write("1\n2\n3\n")
        self.check("cat __test_file __test_file", "1\n2\n3\n\n1\n2\n3\n\n")
        os.remove("__test_file")

    def test_external(self):
        if sys.platform == "linux":
            self.check("touch aoeu\ncat aoeu", "")
