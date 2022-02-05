## ELEN4020 — Data Intensive Computing in Data Science

The objective of the exercise is to introduce the principles of the MapReduce framework for
processing big data. The main features in such a framework are the reliable and fault-tolerant
processing techniques employed. While not all problems are solvable by the MapReduce
techniques, a large number of decomposable problems can be divided up to be solved by the
MapReduce technique.


## Lab Objectives
* A simple word count algorithm of a text. This gives the frequencies of occurence of
words in a text excluding stop words.

* Top-K query. The K most frequently occurring words, ignoring stop words, for K =
10, 20.

* An inverted index of the text. This involves listing, for a given list of words, the line
numbers of the text that the words occur. Only list out about 50 lines of the distinct
words: i.e. the first 50 lines with that word.

## Build and Run

To build and run the lab simply type:

```./Lab3.sh```

This script will compile and execute the ```c++``` lab. 

A prompt to enter the list of input files will be presented. You may enter multiple files to process. You must include the full path if not working
in the same directory. The same applies for the the output file. This file contains the word frequency of the input file(s) provided.

A sample run is demonstrated below excluding words of length less than 3 and the following stop words (list found in stopWords.txt):

"that then that they there with what when what which were their have from this your some"


## Sample Output

### small input text

./Lab3.sh

Cleaning working directory

rm  -f *.o *.out main

Building Lab...

g++ -std=c++17 -static-libstdc++ src/main.cpp -o main.out -lpthread -Iinclude

Building Done...

Running Lab...

Please enter list of input files

small.txt

Please enter output file

output.txt

#### Beginning Threaded MapReduce Job

================================

Job:
  - Run Time:      	0.395077
  - Avalable Threads:   4

Map:
  - Runners:  4
    - Total Run Time:   0.255188
    - Average Run Time: 0.063797
    - Minimum Run Time: 1e-06
    - Maximum Run Time: 0.255168
  - Tasks:            1
    - Average Run Time: 0.21991
    - Minimum Run Time: 0.21991
    - Maximum Run Time: 0.255168

Shuffle:
  - Run Time:      	0.007492

Reduce:
  - Runners:  4
    - Total Run Time:   0.524318
    - Average Run Time: 0.13108
    - Minimum Run Time: 0.131057
    - Maximum Run Time: 0.131113
  - Tasks:            16554
    - Average Run Time: 3.07555e-05
    - Minimum Run Time: 0.001055
    - Maximum Run Time: 0.131113

#### Beginning MapReduce Job

================================

Job:
  - Run Time:      	0.313262
  - Avalable Threads:   4

Map:
  - Runners:  1
    - Total Run Time:   0.256612
    - Average Run Time: 0.256612
    - Minimum Run Time: 0.256612
    - Maximum Run Time: 0.256612
  - Tasks:            1
    - Average Run Time: 0.218224
    - Minimum Run Time: 0.218224
    - Maximum Run Time: 0.256612

Shuffle:
  - Run Time:      	0.006926

Reduce:
  - Runners:  1
    - Total Run Time:   0.049706
    - Average Run Time: 0.049706
    - Minimum Run Time: 0.049706
    - Maximum Run Time: 0.049706
  - Tasks:            16554
    - Average Run Time: 2.19899e-06
    - Minimum Run Time: 2e-06
    - Maximum Run Time: 0.049706

#### Enter K Query

============

10

upon: 816

been: 723

states: 704

into: 675

american: 599

said: 584

could: 555

them: 538

would: 519

more: 517

#### Enter K Query

============

20

upon: 816

been: 723

states: 704

into: 675

american: 599

said: 584

could: 555

them: 538

would: 519

more: 517

government: 499

very: 490

holmes: 461

than: 413

other: 400

will: 393

time: 392

over: 392

made: 374

before: 371


#### Please enter a list of words to search for :

============================================

upon been states into american said could them would more government very holmes than other will time over made before

Word found: upon

upon : 77 81 81 99 115 119 119 125 141 155 159 169 187 197 305 322 432 432 450 464 464 466 513 551 585 604 626 626 628 630 630 634 634 646 664 716 728 738 760 776 776 802 854 868 878 886 886 910 914 914 


Word found: been

been : 79 81 93 95 99 99 115 155 159 183 249 249 249 330 362 370 428 434 458 464 464 468 508 549 567 567 567 567 579 614 620 626 626 632 650 670 704 704 718 726 772 832 864 914 944 950 950 1020 1026 1061 


Word found: states

states : 1362 1827 1853 2023 2023 2095 3977 5282 5285 5286 5292 5296 5298 5320 5321 5369 5371 5416 5503 5512 5522 5540 5694 5695 5792 5845 5891 5892 5924 5938 5944 5946 5948 5950 5985 6514 6518 6519 6524 6530 6587 6596 6982 7088 7137 7695 7755 7758 7982 8167 


Word found: into

into : 77 89 99 103 131 167 283 320 322 322 322 348 354 354 362 398 406 420 450 450 462 464 466 488 496 513 515 549 565 567 604 618 622 678 678 684 690 716 798 802 824 886 954 958 984 1026 1053 1067 1069 1071 


Word found: american

american : 708 712 1989 2099 4051 4065 4269 4285 4291 4291 4299 5584 5612 5689 5700 5708 5723 5755 5757 5801 5857 5859 5952 5968 5976 6015 6025 6028 6106 6114 6155 6221 6311 6492 6534 6571 6689 6734 6773 6953 6963 6966 6967 6981 6989 6999 7005 7006 7017 7018 


Word found: said

said : 95 99 115 119 129 139 145 157 163 167 169 171 177 191 193 199 255 281 283 303 311 352 364 366 390 410 458 480 502 508 553 579 587 606 618 652 654 664 670 678 706 708 710 716 720 722 726 726 728 734 


Word found: could

could : 101 101 127 141 159 191 197 328 332 332 334 346 346 352 354 420 432 432 464 468 486 488 508 541 581 606 650 674 716 716 726 774 774 774 804 814 822 822 880 990 990 990 1024 1026 1026 1026 1026 1030 1045 1045 


Word found: them

them : 273 332 340 348 354 362 466 565 567 626 720 720 804 828 830 830 830 980 980 980 1018 1022 1032 1032 1032 1053 1061 1101 1101 1105 1141 1141 1231 1231 1275 1295 1313 1334 1340 1340 1356 1362 1366 1492 1534 1550 1584 1672 1736 1759 


Word found: would

would : 77 77 95 149 159 161 185 269 273 281 297 424 458 464 476 492 547 549 567 577 626 630 670 690 704 710 710 712 712 716 716 720 726 726 736 744 748 748 750 774 776 778 846 888 914 914 914 918 950 964 


Word found: more

more : 77 89 89 191 193 338 346 366 464 492 492 529 579 581 587 597 622 638 650 670 682 690 720 772 874 884 934 944 948 964 968 992 1026 1049 1051 1065 1113 1171 1207 1275 1275 1295 1305 1307 1350 1350 1360 1364 1370 1378 


Word found: government

government : 2023 5182 5740 5752 5758 5775 5823 6006 6017 6020 6055 6059 6089 6136 6157 6162 6187 6298 6454 6872 6884 6886 7170 7232 7256 7316 7447 7454 7471 7523 7534 7539 7584 7602 7660 7670 7674 7728 7745 7749 7752 7761 7804 7991 8034 8256 8303 8309 8364 8382 


Word found: very

very : 93 99 119 129 159 231 257 259 269 283 320 364 366 366 410 420 468 488 567 574 579 597 604 610 622 626 630 646 668 670 674 682 684 692 702 704 708 708 714 714 718 720 734 748 750 760 780 800 824 854 


Word found: holmes

holmes : 27 40 50 77 79 79 81 95 129 133 143 147 157 163 167 171 177 181 183 189 193 197 199 255 283 305 311 320 420 422 424 450 464 464 466 466 504 508 515 531 553 555 559 565 565 569 571 579 587 599 


Word found: than

than : 77 159 273 338 346 422 464 466 492 492 571 622 638 670 690 720 720 784 800 824 884 934 944 948 950 974 1010 1032 1045 1049 1087 1091 1101 1145 1149 1149 1207 1213 1275 1293 1295 1295 1336 1370 1374 1378 1386 1398 1580 1592 


Word found: other

other : 7 13 77 79 161 211 311 334 338 354 362 450 450 450 622 626 702 724 798 910 912 914 936 998 1002 1022 1026 1028 1032 1032 1051 1053 1121 1141 1143 1157 1221 1221 1221 1243 1275 1279 1295 1299 1299 1311 1356 1356 1360 1370 


Word found: will

will : 119 169 175 245 273 273 281 283 285 315 332 332 390 398 398 398 402 406 406 410 410 438 440 444 446 448 450 496 498 500 529 571 571 571 614 618 622 654 664 726 760 764 768 774 802 868 920 928 948 948 


Word found: time

time : 79 79 169 390 406 418 506 606 626 632 760 760 776 776 778 908 912 914 914 924 926 952 968 976 990 1022 1101 1105 1123 1249 1281 1299 1336 1360 1362 1398 1492 1528 1534 1546 1562 1582 1592 1592 1592 1724 1728 1728 1825 1827 


Word found: over

over : 5 83 115 159 191 315 338 432 599 662 682 692 704 726 736 774 874 886 934 976 990 994 994 1020 1022 1045 1053 1065 1067 1067 1071 1083 1101 1105 1229 1231 1275 1281 1283 1287 1291 1360 1398 1462 1464 1496 1538 1550 1550 1592 


Word found: made

made : 139 195 249 320 410 428 466 549 567 569 577 650 704 878 886 936 970 1016 1026 1083 1083 1091 1103 1149 1199 1267 1269 1295 1299 1336 1356 1398 1510 1550 1584 1584 1730 1827 1843 1845 1853 1881 2120 2140 2144 2172 2230 2238 2238 2240 


Word found: before

before : 6 83 123 167 189 322 322 346 348 352 354 362 456 508 565 622 748 780 892 968 982 1028 1065 1069 1103 1103 1149 1153 1225 1291 1305 1362 1362 1374 1400 1424 1424 1436 1458 1474 1534 1536 1538 1550 1554 1584 1592 1596 1634 1642 

### big input text

./Lab3.sh

Cleaning working directory

rm  -f *.o *.out main

Building Lab...

g++ -std=c++17 -static-libstdc++ src/main.cpp -o main.out -lpthread -Iinclude

Building Done...

Running Lab...

Please enter list of input files

big.txt

Please enter output file

output.txt

#### Beginning Threaded MapReduce Job

================================

Job:
  - Run Time:      	1.21587
  - Avalable Threads:   4

Map:
  - Runners:  4
    - Total Run Time:   0.889467
    - Average Run Time: 0.222367
    - Minimum Run Time: 3e-06
    - Maximum Run Time: 0.889445
  - Tasks:            1
    - Average Run Time: 0.813333
    - Minimum Run Time: 0.813333
    - Maximum Run Time: 0.889445

Shuffle:
  - Run Time:      	0.018169

Reduce:
  - Runners:  4
    - Total Run Time:   1.22688
    - Average Run Time: 0.30672
    - Minimum Run Time: 0.30665
    - Maximum Run Time: 0.306803
  - Tasks:            34661
    - Average Run Time: 3.40836e-05
    - Minimum Run Time: 0.00196
    - Maximum Run Time: 0.306803

#### Beginning MapReduce Job

================================

Job:
  - Run Time:      	1.00831
  - Avalable Threads:   4

Map:
  - Runners:  1
    - Total Run Time:   0.875733
    - Average Run Time: 0.875733
    - Minimum Run Time: 0.875733
    - Maximum Run Time: 0.875733
  - Tasks:            1
    - Average Run Time: 0.796448
    - Minimum Run Time: 0.796448
    - Maximum Run Time: 0.875733

Shuffle:
  - Run Time:      	0.014253

Reduce:
  - Runners:  1
    - Total Run Time:   0.118306
    - Average Run Time: 0.118306
    - Minimum Run Time: 0.118306
    - Maximum Run Time: 0.118306
  - Tasks:            34661
    - Average Run Time: 2.46493e-06
    - Minimum Run Time: 2e-06
    - Maximum Run Time: 0.118306

#### Enter K Query

============

10

said: 3456

been: 2598

them: 2218

into: 2120

more: 1988

would: 1949

prince: 1893

only: 1861

pierre: 1785

could: 1695

#### Enter K Query

============

20

said: 3456

been: 2598

them: 2218

into: 2120

more: 1988

would: 1949

prince: 1893

only: 1861

pierre: 1785

could: 1695

will: 1564

time: 1509

about: 1492

after: 1485

other: 1484

such: 1405

before: 1347

very: 1335

should: 1290

over: 1259

#### Please enter a list of words to search for :

============================================

said been them into more would prince only pierre could will time about after other such before very should over

Word found: said

said : 95 99 115 119 129 139 145 157 163 167 169 171 177 191 193 199 255 281 283 303 311 352 364 366 390 410 458 480 502 508 553 579 587 606 618 652 654 664 670 678 706 708 710 716 720 722 726 726 728 734 


Word found: been

been : 79 81 93 95 99 99 115 155 159 183 249 249 249 330 362 370 428 434 458 464 464 468 508 549 567 567 567 567 579 614 620 626 626 632 650 670 704 704 718 726 772 832 864 914 944 950 950 1020 1026 1061 


Word found: them

them : 273 332 340 348 354 362 466 565 567 626 720 720 804 828 830 830 830 980 980 980 1018 1022 1032 1032 1032 1053 1061 1101 1101 1105 1141 1141 1231 1231 1275 1295 1313 1334 1340 1340 1356 1362 1366 1492 1534 1550 1584 1672 1736 1759 


Word found: into

into : 77 89 99 103 131 167 283 320 322 322 322 348 354 354 362 398 406 420 450 450 462 464 466 488 496 513 515 549 565 567 604 618 622 678 678 684 690 716 798 802 824 886 954 958 984 1026 1053 1067 1069 1071 


Word found: more

more : 77 89 89 191 193 338 346 366 464 492 492 529 579 581 587 597 622 638 650 670 682 690 720 772 874 884 934 944 948 964 968 992 1026 1049 1051 1065 1113 1171 1207 1275 1275 1295 1305 1307 1350 1350 1360 1364 1370 1378 


Word found: would

would : 77 77 95 149 159 161 185 269 273 281 297 424 458 464 476 492 547 549 567 577 626 630 670 690 704 710 710 712 712 716 716 720 726 726 736 744 748 748 750 774 776 778 846 888 914 914 914 918 950 964 


Word found: prince

prince : 237 8095 15826 25739 26924 54332 54342 54351 54356 54377 54384 54390 54395 54435 54447 54454 54471 54481 54484 54495 54503 54531 54542 54549 54574 54580 54638 54641 54726 54801 54810 54831 54901 54914 54930 54931 54933 54944 54946 54949 54960 54964 54972 54974 54978 54983 54992 54993 55000 55002 


Word found: only

only : 141 237 338 348 348 360 394 571 650 670 690 762 778 822 840 862 888 914 934 990 1022 1028 1087 1097 1101 1149 1157 1217 1221 1235 1245 1257 1275 1279 1297 1311 1334 1356 1374 1398 1398 1402 1504 1526 1532 1550 1584 1584 1592 1606 


Word found: pierre

pierre : 54655 54661 54665 54670 54679 54698 54703 54864 54877 54880 54890 54930 54938 54940 54957 54962 54971 55133 55150 55155 55176 55180 55187 55196 55206 55221 55246 55254 55267 55282 55344 55356 55426 55447 55457 55472 55479 55484 55487 55509 55515 55530 55539 55542 55561 55569 55576 55592 55609 55612 


Word found: could

could : 101 101 127 141 159 191 197 328 332 332 334 346 346 352 354 420 432 432 464 468 486 488 508 541 581 606 650 674 716 716 726 774 774 774 804 814 822 822 880 990 990 990 1024 1026 1026 1026 1026 1030 1045 1045 


Word found: will

will : 119 169 175 245 273 273 281 283 285 315 332 332 390 398 398 398 402 406 406 410 410 438 440 444 446 448 450 496 498 500 529 571 571 571 614 618 622 654 664 726 760 764 768 774 802 868 920 928 948 948 


Word found: time

time : 79 79 169 390 406 418 506 606 626 632 760 760 776 776 778 908 912 914 914 924 926 952 968 976 990 1022 1101 1105 1123 1249 1281 1299 1336 1360 1362 1398 1492 1528 1534 1546 1562 1582 1592 1592 1592 1724 1728 1728 1825 1827 


Word found: about

about : 13 15 16 265 334 338 346 362 428 428 428 565 604 630 664 706 714 742 780 786 802 804 830 834 934 960 980 992 994 1032 1075 1099 1103 1109 1119 1141 1143 1149 1149 1177 1229 1235 1269 1285 1356 1358 1386 1398 1450 1458 


Word found: after

after : 320 332 464 567 567 628 652 662 674 720 736 736 742 776 778 778 778 958 980 994 1028 1040 1091 1113 1113 1125 1225 1362 1378 1398 1462 1522 1570 1750 1752 1829 1855 1885 1985 2023 2037 2232 2334 2364 2430 2530 2536 2561 2719 2841 


Word found: other

other : 7 13 77 79 161 211 311 334 338 354 362 450 450 450 622 626 702 724 798 910 912 914 936 998 1002 1022 1026 1028 1032 1032 1051 1053 1121 1141 1143 1157 1221 1221 1221 1243 1275 1279 1295 1299 1299 1311 1356 1356 1360 1370 


Word found: such

such : 77 77 127 169 191 352 420 422 567 654 674 678 716 720 738 774 774 778 804 822 1026 1026 1055 1061 1081 1299 1362 1374 1384 1386 1386 1472 1476 1494 1534 1538 1568 1568 1584 1630 1726 1740 1742 1750 1750 1759 1769 1769 1825 1829 


Word found: before

before : 6 83 123 167 189 322 322 346 348 352 354 362 456 508 565 622 748 780 892 968 982 1028 1065 1069 1103 1103 1149 1153 1225 1291 1305 1362 1362 1374 1400 1424 1424 1436 1458 1474 1534 1536 1538 1550 1554 1584 1592 1596 1634 1642 


Word found: very

very : 93 99 119 129 159 231 257 259 269 283 320 364 366 366 410 420 468 488 567 574 579 597 604 610 622 626 630 646 668 670 674 682 684 692 702 704 708 708 714 714 718 720 734 748 750 760 780 800 824 854 


Word found: should

should : 9 89 165 185 187 211 273 315 340 348 352 352 432 547 587 674 674 708 716 726 734 742 762 822 912 934 934 968 1026 1032 1077 1117 1149 1149 1177 1187 1243 1243 1299 1334 1356 1386 1410 1492 1522 1538 1538 1546 1568 1632 


Word found: over

over : 5 83 115 159 191 315 338 432 599 662 682 692 704 726 736 774 874 886 934 976 990 994 994 1020 1022 1045 1053 1065 1067 1067 1071 1083 1101 1105 1229 1231 1275 1281 1283 1287 1291 1360 1398 1462 1464 1496 1538 1550 1550 1592 

Acknowledgement
===========================================

[1] Andrea C. Arpaci-Dusseau, Remzi H. Arpaci-Dusseau,David E. Culler, Joseph M. Hellerstein, and David A. Patterson. High-performance sorting on networks of workstations. In Proceedings of the 1997 ACM SIGMOD International Conference on Management of Data, Tucson,Arizona, May 1997.

[2] Remzi H. Arpaci-Dusseau, Eric Anderson, Noah Treuhaft, David E. Culler, Joseph M. Hellerstein, David Patterson, and Kathy Yelick. Cluster I/O with River:
Making the fast case common. In Proceedings of the Sixth Workshop on Input/Output in Parallel and Distributed Systems (IOPADS ’99), pages 10–22, Atlanta, Georgia,
May 1999.

[3] Arash Baratloo, Mehmet Karaul, Zvi Kedem, and Peter Wyckoff. Charlotte: Metacomputing on the web. In Proceedings of the 9th International Conference on Parallel and Distributed Computing Systems, 1996.

[4] Luiz A. Barroso, Jeffrey Dean, and Urs Holzle. ¨ Web search for a planet: The Google cluster architecture. IEEE Micro, 23(2):22–28, April 2003.

[5] A Thilenius (2018) MapReduce [source code]. https://github.com/AThilenius/MapReduce

[6] John Bent, Douglas Thain, Andrea C.Arpaci-Dusseau, Remzi H. Arpaci-Dusseau, and Miron Livny. Explicit control in a batch-aware distributed file system. In Proceedings of the 1st USENIX Symposium on Networked Systems Design and Implementation NSDI, March 2004.

[7] Guy E. Blelloch. Scans as primitive parallel operations. IEEE Transactions on Computers, C-38(11), November 1989.

[8] Armando Fox, Steven D. Gribble, Yatin Chawathe, Eric A. Brewer, and Paul Gauthier. Cluster-based scalable network services. In Proceedings of the 16th ACM
Symposium on Operating System Principles, pages 78–91, Saint-Malo, France, 1997.

[9] Sanjay Ghemawat, Howard Gobioff, and Shun-Tak Leung. The Google file system. In 19th Symposium on Operating Systems Principles, pages 29–43, Lake George,
New York, 2003.

[10] https://developer-tech.com/news/2015/feb/19/mapreduce-framework-cc-open-sourced-google/
