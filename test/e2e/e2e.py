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
        self.check("echo Hello", "Hello\n")

    def test_echo_with_space(self):
        self.check("echo Hello   ", "Hello\n")

    def test_echo_long(self):
        self.check("echo Hello Hello                      Hello",
                   "Hello Hello Hello\n")

    def test_echo_with_double_quote(self):
        self.check("echo \"Hello\"", "Hello\n")

    def test_echo_with_single_quote(self):
        self.check("echo \'Hello\'", "Hello\n")

    def test_echo_with_single_quote_long(self):
        self.check("echo \'Hello, world!\'", "Hello, world!\n")

    def test_echo_with_single_quoted_command(self):
        self.check("echo 'echo 1 | xargs touch'", "echo 1 | xargs touch\n")

    def test_echo_with_double_quoted_command(self):
        self.check("echo \"echo 1 | xargs touch\"", "echo 1 | xargs touch\n")

    def test_simple_substitution(self):
        self.check("echo $USER", os.getenv("USER") + "\n")

    def test_echo_substitution(self):
        self.check("a=Hello\necho $a", "Hello\n")

    def test_double_quoted_echo_substitution(self):
        self.check("a=Hello\necho \"$a\"", "Hello\n")

    def test_exit_substitution(self):
        self.check("a=ex\nb=it\n$a$b\necho aoeu", "")

    def test_pwd(self):
        self.check("pwd", os.getcwd() + "\n")

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
            f.write("1\n2\n3\n")
        self.check("wc __test_file", "4 3 7 __test_file\n")
        os.remove("__test_file")


    def test_wc_rn(self):
        with open("__test_file", "w") as f:
            f.write("1\r\n2\r\n3\r\n")
        self.check("wc __test_file", "4 3 10 __test_file\n")
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
            os.remove("aoeu")

    def test_simple_pipe_with_xargs_and_touch(self):
        if sys.platform == "linux":
            self.check("echo aoeu | xargs touch", "")
            self.assertTrue(os.path.isfile("aoeu"))
            os.remove("aoeu")

    def test_pipe_with_xargs_and_echo(self):
        with open("__test_file", "w") as f:
            f.write("1\n2\n3\n")
        self.check("cat __test_file | xargs echo", "1 2 3\n")
        os.remove("__test_file")

    def test_pipe_with_xargs_and_echo_twice(self):
        with open("__test_file", "w") as f:
            f.write("1\n2\n3\n")
        self.check("cat __test_file | xargs echo | xargs echo", "1 2 3\n")
        os.remove("__test_file")

    def test_pipe_with_xargs_and_touch(self):
        with open("__test_file", "w") as f:
            f.write("1\n2\n3\n")
        self.check("cat __test_file | xargs touch", "")
        self.assertTrue(os.path.isfile("1"))
        self.assertTrue(os.path.isfile("2"))
        self.assertTrue(os.path.isfile("3"))
        os.remove("1")
        os.remove("2")
        os.remove("3")
        os.remove("__test_file")

    def test_cat_with_single_quotes(self):
        with open("1", "w") as f:
            f.write("1\n")
        with open("2", "w") as f:
            f.write("2\n")
        with open("3", "w") as f:
            f.write("3\n")
        with open("1 2 3", "w") as f:
            f.write("1 2 3\n")
        self.check("cat '1 2 3'", "1 2 3\n\n")
        os.remove("1")
        os.remove("2")
        os.remove("3")
        os.remove("1 2 3")

    def test_cat_with_double_quotes(self):
        with open("1", "w") as f:
            f.write("1\n")
        with open("2", "w") as f:
            f.write("2\n")
        with open("3", "w") as f:
            f.write("3\n")
        with open("1 2 3", "w") as f:
            f.write("1 2 3\n")
        self.check("cat \"1 2 3\"", "1 2 3\n\n")
        os.remove("1")
        os.remove("2")
        os.remove("3")
        os.remove("1 2 3")
