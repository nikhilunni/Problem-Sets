.data

# syscall constants
PRINT_INT = 1
PRINT_CHAR = 11

# stats_t offsets
oldest = 0
youngest = 1
total_salary = 4
average_salary = 8

# limit constants
UINT8_MAX = 255

################################## SIMPLE TREE #################################
simple_tree:	.word	p0x8910028	0	0	0	0	0
p0x8910028:	.word	p0x8910040	p0x8910050	p0x8910060	p0x8910070	0
p0x8910040:
	.byte	32
	.word	60000
p0x8910050:
	.byte	47
	.word	40000
p0x8910060:
	.byte	22
	.word	16000
p0x8910070:
	.byte	131
	.word	4000

################################## MEDIUM TREE #################################
medium_tree:	.word	p0x9925190	0	0	p0x9925028	0	0
p0x9925190:	.word	p0x99251a0	p0x99251b0	0
p0x99251a0:
	.byte	15
	.word	10000
p0x99251b0:
	.byte	49
	.word	50000
p0x9925028:	.word	p0x9925048	p0x99250a0	0	0	0	p0x9925118
p0x9925048:	.word	p0x9925060	p0x9925070	p0x9925080	p0x9925090	0
p0x9925060:
	.byte	32
	.word	60000
p0x9925070:
	.byte	47
	.word	40000
p0x9925080:
	.byte	22
	.word	16000
p0x9925090:
	.byte	131
	.word	4000
p0x99250a0:	.word	p0x99250c0	0	0	0	0	0
p0x99250c0:	.word	p0x99250d8	p0x99250e8	p0x99250f8	p0x9925108	0
p0x99250d8:
	.byte	32
	.word	60000
p0x99250e8:
	.byte	47
	.word	40000
p0x99250f8:
	.byte	22
	.word	16000
p0x9925108:
	.byte	131
	.word	4000
p0x9925118:	.word	p0x9925138	0	0	0	0	0
p0x9925138:	.word	p0x9925150	p0x9925160	p0x9925170	p0x9925180	0
p0x9925150:
	.byte	32
	.word	60000
p0x9925160:
	.byte	47
	.word	40000
p0x9925170:
	.byte	22
	.word	16000
p0x9925180:
	.byte	131
	.word	4000

################################## COMPLEX TREE ################################
complex_tree:	.word	0	p0x91e1028	p0x91e11e0	p0x91e1398	p0x91e1550	p0x91e1708
p0x91e1028:	.word	p0x91e11b0	0	0	p0x91e1048	0	0
p0x91e11b0:	.word	p0x91e11c0	p0x91e11d0	0
p0x91e11c0:
	.byte	15
	.word	10000
p0x91e11d0:
	.byte	49
	.word	50000
p0x91e1048:	.word	p0x91e1068	p0x91e10c0	0	0	0	p0x91e1138
p0x91e1068:	.word	p0x91e1080	p0x91e1090	p0x91e10a0	p0x91e10b0	0
p0x91e1080:
	.byte	32
	.word	60000
p0x91e1090:
	.byte	47
	.word	40000
p0x91e10a0:
	.byte	22
	.word	16000
p0x91e10b0:
	.byte	131
	.word	4000
p0x91e10c0:	.word	p0x91e10e0	0	0	0	0	0
p0x91e10e0:	.word	p0x91e10f8	p0x91e1108	p0x91e1118	p0x91e1128	0
p0x91e10f8:
	.byte	32
	.word	60000
p0x91e1108:
	.byte	47
	.word	40000
p0x91e1118:
	.byte	22
	.word	16000
p0x91e1128:
	.byte	131
	.word	4000
p0x91e1138:	.word	p0x91e1158	0	0	0	0	0
p0x91e1158:	.word	p0x91e1170	p0x91e1180	p0x91e1190	p0x91e11a0	0
p0x91e1170:
	.byte	32
	.word	60000
p0x91e1180:
	.byte	47
	.word	40000
p0x91e1190:
	.byte	22
	.word	16000
p0x91e11a0:
	.byte	137
	.word	4000
p0x91e11e0:	.word	p0x91e1368	0	0	p0x91e1200	p0x91e1728	0
p0x91e1368:	.word	p0x91e1378	p0x91e1388	0
p0x91e1378:
	.byte	15
	.word	10000
p0x91e1388:
	.byte	49
	.word	50000
p0x91e1200:	.word	p0x91e1220	p0x91e1278	0	0	0	p0x91e12f0
p0x91e1220:	.word	p0x91e1238	p0x91e1248	p0x91e1258	p0x91e1268	0
p0x91e1238:
	.byte	32
	.word	60000
p0x91e1248:
	.byte	47
	.word	40000
p0x91e1258:
	.byte	22
	.word	16000
p0x91e1268:
	.byte	131
	.word	4000
p0x91e1278:	.word	p0x91e1298	0	0	0	0	0
p0x91e1298:	.word	p0x91e12b0	p0x91e12c0	p0x91e12d0	p0x91e12e0	0
p0x91e12b0:
	.byte	32
	.word	60000
p0x91e12c0:
	.byte	47
	.word	40000
p0x91e12d0:
	.byte	22
	.word	16000
p0x91e12e0:
	.byte	131
	.word	4000
p0x91e12f0:	.word	p0x91e1310	0	0	0	0	0
p0x91e1310:	.word	p0x91e1328	p0x91e1338	p0x91e1348	p0x91e1358	0
p0x91e1328:
	.byte	32
	.word	60000
p0x91e1338:
	.byte	47
	.word	40000
p0x91e1348:
	.byte	22
	.word	16000
p0x91e1358:
	.byte	131
	.word	4000
p0x91e1728:	.word	p0x91e1748	p0x91e17a0	0	0	0	p0x91e1818
p0x91e1748:	.word	p0x91e1760	p0x91e1770	p0x91e1780	p0x91e1790	0
p0x91e1760:
	.byte	32
	.word	10000
p0x91e1770:
	.byte	47
	.word	40000
p0x91e1780:
	.byte	22
	.word	16000
p0x91e1790:
	.byte	131
	.word	4000
p0x91e17a0:	.word	p0x91e17c0	0	0	0	0	0
p0x91e17c0:	.word	p0x91e17d8	p0x91e17e8	p0x91e17f8	p0x91e1808	0
p0x91e17d8:
	.byte	32
	.word	60000
p0x91e17e8:
	.byte	47
	.word	40000
p0x91e17f8:
	.byte	22
	.word	16000
p0x91e1808:
	.byte	131
	.word	4000
p0x91e1818:	.word	p0x91e1838	0	0	0	0	0
p0x91e1838:	.word	p0x91e1850	p0x91e1860	p0x91e1870	p0x91e1880	0
p0x91e1850:
	.byte	32
	.word	60000
p0x91e1860:
	.byte	47
	.word	40000
p0x91e1870:
	.byte	22
	.word	16000
p0x91e1880:
	.byte	131
	.word	4000
p0x91e1398:	.word	p0x91e1520	0	0	p0x91e13b8	0	0
p0x91e1520:	.word	p0x91e1530	p0x91e1540	0
p0x91e1530:
	.byte	15
	.word	10000
p0x91e1540:
	.byte	49
	.word	50000
p0x91e13b8:	.word	p0x91e13d8	p0x91e1430	0	0	0	p0x91e14a8
p0x91e13d8:	.word	p0x91e13f0	p0x91e1400	p0x91e1410	p0x91e1420	0
p0x91e13f0:
	.byte	32
	.word	60000
p0x91e1400:
	.byte	47
	.word	40000
p0x91e1410:
	.byte	22
	.word	16000
p0x91e1420:
	.byte	131
	.word	4000
p0x91e1430:	.word	p0x91e1450	0	0	0	0	0
p0x91e1450:	.word	p0x91e1468	p0x91e1478	p0x91e1488	p0x91e1498	0
p0x91e1468:
	.byte	32
	.word	60000
p0x91e1478:
	.byte	47
	.word	40000
p0x91e1488:
	.byte	22
	.word	16000
p0x91e1498:
	.byte	131
	.word	4000
p0x91e14a8:	.word	p0x91e14c8	0	0	0	0	0
p0x91e14c8:	.word	p0x91e14e0	p0x91e14f0	p0x91e1500	p0x91e1510	0
p0x91e14e0:
	.byte	32
	.word	60000
p0x91e14f0:
	.byte	47
	.word	40000
p0x91e1500:
	.byte	22
	.word	16000
p0x91e1510:
	.byte	131
	.word	4000
p0x91e1550:	.word	p0x91e16d8	0	0	p0x91e1570	0	0
p0x91e16d8:	.word	p0x91e16e8	p0x91e16f8	0
p0x91e16e8:
	.byte	15
	.word	10000
p0x91e16f8:
	.byte	49
	.word	50000
p0x91e1570:	.word	p0x91e1590	p0x91e15e8	0	0	0	p0x91e1660
p0x91e1590:	.word	p0x91e15a8	p0x91e15b8	p0x91e15c8	p0x91e15d8	0
p0x91e15a8:
	.byte	32
	.word	60000
p0x91e15b8:
	.byte	47
	.word	20000
p0x91e15c8:
	.byte	22
	.word	16000
p0x91e15d8:
	.byte	131
	.word	4000
p0x91e15e8:	.word	p0x91e1608	0	0	0	0	0
p0x91e1608:	.word	p0x91e1620	p0x91e1630	p0x91e1640	p0x91e1650	0
p0x91e1620:
	.byte	32
	.word	60000
p0x91e1630:
	.byte	47
	.word	40000
p0x91e1640:
	.byte	22
	.word	16000
p0x91e1650:
	.byte	131
	.word	4000
p0x91e1660:	.word	p0x91e1680	0	0	0	0	0
p0x91e1680:	.word	p0x91e1698	p0x91e16a8	p0x91e16b8	p0x91e16c8	0
p0x91e1698:
	.byte	32
	.word	60000
p0x91e16a8:
	.byte	47
	.word	40000
p0x91e16b8:
	.byte	22
	.word	16000
p0x91e16c8:
	.byte	131
	.word	4000
p0x91e1708:	.word	p0x91e1890	0	0	0	0	0
p0x91e1890:	.word	p0x91e18a0	p0x91e18b0	0
p0x91e18a0:
	.byte	15
	.word	10000
p0x91e18b0:
	.byte	49
	.word	50000

.text

# print_int and space ##########################################################
#
# argument $a0: number to print

print_int_and_space:
	li	$v0, PRINT_INT			# load the syscall option for printing ints
	syscall					# print the number

	li   	$a0, ' '       			# print a black space
	li	$v0, PRINT_CHAR			# load the syscall option for printing chars
	syscall					# print the char
	
	jr	$ra				# return to the calling procedure


# compute stats wrapper ########################################################
#
# calls compute_stats and uses the results to compute the average salary

compute_stats_wrapper:
	sub	$sp, $sp, 8
	sw	$ra, 0($sp)
	sw	$a1, 4($sp)			# stats

	jal	compute_stats			# $a0 and $a1 have correct values
	lw	$a1, 4($sp)			# stats
	bne	$v0, 0, csw_average		# !(population == 0)
	sw	$zero, average_salary($a1)	# stats->average_salary = 0
	j	csw_done

csw_average:
	lw	$t0, total_salary($a1)		# stats->total_salary
	div	$t0, $t0, $v0			# stats->total_salary / population
	sw	$t0, average_salary($a1)	# stats->average_salary = ...

csw_done:
	lw	$ra, 0($sp)
	add	$sp, $sp, 8
	jr	$ra


# main function ################################################################
#
# tests your compute_stats function (via compute_stats_wrapper)

main:
	sub	$sp, $sp, 16
	sw	$ra, 0($sp)

	# allocate 4($sp) through $15(sp) for stats
	la	$a1, 4($sp)
	sb	$zero, oldest($a1)
	li	$t0, UINT8_MAX
	sb	$t0, youngest($a1)
	sw	$zero, total_salary($a1)
	sw	$zero, average_salary($a1)

	# uncomment an additional test case each time you get the previous one working!
	#la	$a0, simple_tree
	#la	$a0, medium_tree
	la	$a0, complex_tree

	jal	compute_stats_wrapper

	# compile and run p2.cpp to get the correct output for each test case
	lbu	$a0, 4+oldest($sp)
	jal	print_int_and_space
	lbu	$a0, 4+youngest($sp)
	jal	print_int_and_space
	lw	$a0, 4+total_salary($sp)
	jal	print_int_and_space
	lw	$a0, 4+average_salary($sp)
	jal	print_int_and_space

	lw	$ra, 0($sp)
	add	$sp, $sp, 16
	jr	$ra
