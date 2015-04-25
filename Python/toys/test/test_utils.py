import unittest
from toys.utils import super_len

class UtilsTest(unittest.TestCase):

    def setUp(self):
        self.test_dictionary = {'one':1,'two':2}

    def test_super_len(self):
        self.assertEqual(2,super_len(test_dictionary))

if __name__ == '__main__':
    unittest.main()
        
        

   
