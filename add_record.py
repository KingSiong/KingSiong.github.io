import sys
import json
import time

def get_time():
    now = time.localtime()
    now_time = time.strftime("%Y-%m-%d %H:%M:%S",now)
    return now_time

title = sys.argv[1]
source = sys.argv[2]
submit_time = get_time()

with open('./' + title + '.md') as file:
    record = {}
    for line in file:
        str_lst = line.split(":")
        record[str_lst[0]] = str_lst[1]
        pass
    with open('./record.json') as file_read:
        json_data = json.load(file_read)
        record['title'] = title
        record['source'] = source + '.html'
        record['time'] = submit_time
        json_data['record'].append(record)
        with open('./record.json', 'w') as file_write:
            json.dump(json_data, file_write, sort_keys=True, indent=4, separators=(',', ': '))