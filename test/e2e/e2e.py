import unittest
import subprocess
import os


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

    def test_pwd(self):
        self.check("pwd", os.getcwd())

    def test_echo_after_exit(self):
        self.check("exit\necho Hello", "")
