import sys, csv

times = ['10am', '11am', '12pm', '1pm', '2pm', '3pm', '4pm', '5pm', '6pm', '7pm', '8pm', '9pm']
nz_count = 0    # non-zero count

in_f = open("schedule.csv", 'rU')
reader = csv.reader(in_f)
for (i_row, row) in enumerate(reader):
    if i_row == 0: continue
    time = row[0].strip()
    if time not in times:
        print "Unrecognized time: %s" % time
    else: 
        for v in row[1:]:
	    if v.strip() != "0":
                nz_count = nz_count + 1

total = len(times) * 6   # total number of slots
if nz_count < (total/3):
    print "not enough available times specified: only %s non-zero entries, need %s" % (nz_count, total/3)
else:
    print "Validated"
    
