import unittest
import subprocess


class SmokeTest(unittest.TestCase):
    def check(self, test_input, correct_answer):
        proc = subprocess.Popen(["./build/topsh"], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
        out = proc.communicate(test_input.encode())[0].decode("UTF-8")

        self.assertEqual(out, correct_answer)
        self.assertEqual(proc.returncode, 0)

    def test_basic(self):
        self.check("Hi", "Hi")
