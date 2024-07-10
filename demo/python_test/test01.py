import unittest
from tool_report import HTMLTestRunner
 
# 定义一些测试用例
class TestExample(unittest.TestCase):
    def test_one(self):
        self.assertEqual(1, 1)
    
    def test_two(self):
        self.assertEqual(2, 2)
 
# 收集测试用例
def suite():
    test_suite = unittest.TestSuite()
    test_suite.addTest(TestExample('test_one'))
    test_suite.addTest(TestExample('test_two'))
    return test_suite
 
# 运行测试并生成报告
with open('TestReport.html', 'wb') as f:
    runner = HTMLTestRunner.HTMLTestRunner(stream=f, title='Test Report', description='Description of this test.')
    runner.run(suite())

