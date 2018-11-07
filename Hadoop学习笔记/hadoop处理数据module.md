# hadoop处理数据模版

<br>
<br>
<br>
<br>

## 1 利用hql处理数据

利用hql处理数据需要用到两个文件，handle.py和handle.sql文件，利用python handle.py运行。

- handle.py
```python

#!/usr/bin/env python2.7
# -*- coding:gb18030 -*-
from tool import *
import time

name=__file__[2:-3]
date=sys.argv[1]
user = ''

if len(sys.argv) > 2:
    user = sys.argv[2]
os.putenv('JAVA_HOME', 'java_home_path')

system('cat %s.sql'%name)
system('mkdir '+name)
system('queryengine_path --hivevar user=%s --hivevar date=%s --hivevar date2=%s --hivevar date3=%s --hivevar name=%s --sessionconf engine=wing -f %s.sql > %s/%s'%(user,date,date2,date3,name,name,name,date))

```

handle.py 基本不需要变动，修改handle.sql即可。

- handle.sql

```sql

SET mapred.job.name=${hivevar:user}_${hivevar:date}_${hivevar:name};
SET mapred.job.priority=HIGH;

sessiondb = database 'session:/';
use sessiondb;
create table test_table(user_id string, user_name sring) row format delimited fields terminated by '\t';
load data inpath "data_hdfs_input_path" overwrite into table cuid_sid;  --将hdfs中的数据load为table

INSERT OVERWRITE DIRECTORY 'data_save_path' --存储地址
ROW FORMAT DELIMITED FIELDS TERMINATED BY '\t' --存储\t分隔

SELECT
	*
FROM
    table
```

## 2 利用Map Reduce处理数据

利用Map Reduce处理数据需要用到三个文件，map.py、red.py和run.sh文件，map.py和red.py编写计算逻辑，run.sh文件将数据放到hadoop集群上进行运算。

### 2.1 Map Reduce处理hdfs中数据：

-map.py

```python
# -*-coding:utf-8 -*-

import sys
import os


input_file = os.getenv('map_input_file')
#print  input_file
day = sys.argv[1]

for line in sys.stdin:
    if str1 in input_file:
        print "%s\t%s" % ("", "")


    if str2 in input_file:
        print "%s\t%s" % ("", "")
```

-red.py
```python
import sys

current_word = None
current_count = 0

for line in sys.stdin:
    line = line.strip()
    word, count = line.split("\t", 1)

    count = int(count)
    if current_word == word:
         current_count += count
    else:
        if current_word:
            print "%s\t%s" % (current_word, current_count)
        current_word = word
        current_count = count

if current_word == word:
    print "%s\t%s" % (current_word, current_count)
```
-run.sh

```bash
#!/bin/bash

ipath=""
opath=""

HADOOP=hadoop_path

$HADOOP fs -rmr $opath
$HADOOP  streaming \
        -input  ${ipath} \
        -output ${opath} \
        -partitioner '' \
        -mapper "python map.py" \
        -reducer "python red.py" \
        -file map.py  \
        -file red.py \
        -jobconf mapred.job.priority=VERY_HIGH \
        -jobconf mapred.job.queue.name="" \
        -jobconf mapred.job.name="" \
        -jobconf mapred.reduce.tasks=1000 \
        -jobconf mapred.job.map.capacity=1000 \
        -jobconf mapred.job.reduce.capacity=100 \
        -jobconf num.key.fields.for.partition=1 \
        -jobconf stream.num.map.output.key.fields=1 \
        -cacheArchive ""

if [ $? -ne 0 ];then
    echo "hadoop streaming failed"
    exit 1
else
    ${HADOOP} fs -touchz ${opath}/@manifest
fi

echo "${opath}"
echo "$1 finished"
```

### 2.1 Map Reduce处理hive中数据：

- BdAppCuidSidDau.py (parse数据)

- map.py

```python
# -*- coding:utf-8 -*-
"""
author: fengshuchao(@baidu.com)
date: 2018/07/25
version: 1.0
"""

import sys
import json
import copy
sys.path.append('path_BdAppCuidSidDau.py')
from BdAppCuidSidDau import RecordParser


idx_list = []

output = dict.fromkeys(idx_list, 0)


if __name__ == '__main__':

    record_parser = RecordParser()

    for line in sys.stdin:
        record = record_parser.parser(line)

        #过滤有效record和sid_list

        if type(record).__name__ != 'dict':   #部分bool型
            continue
            
        print '%s$%s$%s\t%s' % (record[''], \
                                   record[''], \
                                   record[''], \
                                   output)
```

- red.py

- run.sh
```sh 
#!/bin/sh
day=$1
INPUT_TABLE=""
INPUT_COLS="*"
INPUT_PROJECT="${INPUT_TABLE}#filter={event_day=${day}}#inputcols=${INPUT_COLS}"
OUTPUT_DIR="ouput_path"

LIB_DIR=
HADOOP_BIN_PATH=

export HADOOP_CLASSPATH=
export LD_LIBRARY_PATH=

${HADOOP_BIN_PATH}/hadoop fs -rmr ${OUTPUT_DIR}

${HADOOP_BIN_PATH}/hadoop streaming -libjars ${LIB_DIR}/upi-mr.jar \
    -jobconf udw.upi.input="${INPUT_PROJECT}" \
    -input "anything" \
    -output ${OUTPUT_DIR} \
    -inputformat com.baidu.udw.mapred.MultiTableInputFormat \
	-partitioner org.apache.hadoop.mapred.lib.KeyFieldBasedPartitioner \
    -mapper "python map.py" \
	-reducer "cat" \
    -file "map.py" \
    -file "BdAppCuidSidDau.py \
    -jobconf mapred.job.queue.name="" \
    -jobconf mapred.job.priority=VERY_HIGH \
    -jobconf mapred.map.tasks=1000 \
    -jobconf mapred.reduce.tasks=1000 \
    -jobconf mapred.job.map.capacity=500 \
    -jobconf mapred.job.reduce.capacity=500 \
    -jobconf num.key.fields.for.partition=1 \
    -jobconf stream.num.map.output.key.fields=2 \
    -jobconf mapred.job.name="" \
    -cacheArchive  \


if [ $? -ne 0 ];then
    echo "M/R Job Info fails"
    exit 1
fi

echo "~~~sucessful~~~"
```




