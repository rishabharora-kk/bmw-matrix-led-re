import sys
import unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from candump_catalog import parse_log, summarize


class TestCatalog(unittest.TestCase):
    def test_parse_fixture(self):
        data = Path(__file__).resolve().parents[1].joinpath('examples/synthetic_can.log').read_text()
        result = summarize(parse_log(data))
        self.assertEqual(len(result), 2)
        self.assertEqual(result[0]['frame_id_hex'], '0x120')
        self.assertEqual(result[0]['samples'], '3')
        self.assertEqual(result[1]['distinct_payloads'], '1')

    def test_rejects_incorrect_data(self):
        with self.assertRaises(ValueError):
            parse_log('(1.0) vcan0 120#0')

    def test_rejects_random_prose(self):
        with self.assertRaises(ValueError):
            parse_log('bad')

    def test_empty(self):
        self.assertEqual(summarize(parse_log('# nothing')), [])


if __name__ == '__main__':
    unittest.main()
