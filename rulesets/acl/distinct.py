#!/usr/bin/env python3


import struct
import re
import math

import struct

import ipaddress
import math

list1=[]
list2=[]
list3_1=[]
list3_2=[]
list4_1=[]
list4_2=[]
list3_11=[]
list3_12=[]
list4_11=[]
list4_12=[]
list3_21=[]
list4_21=[]

list5=[]
list3=[]
list4=[]
dis_sip=[]
dis_dip=[]
dis_sport=[]
dis_dport=[]
dis_protocol=[]

with open('/home/ashok/project_iiitdm/RuleSet_Statstics/acl/acl1_5K.rl','r') as f1:
	lines1=f1.readlines();
	print("Total Rules===",len(lines1))
	print("\n\n")

	
	for l in range(0,len(lines1)):
		space=0;
		for k in range(0,len(lines1[l])):
			if(lines1[l][k]==' '):
				space=space+1;
		#print(space)
		if(space==8):
			#print("yes")
			a = str(lines1[l])
			a = a.split(" ")
			#print(a)
			list1.append(a[0])
			list2.append(a[1])
			list5.append(a[8])
			list3_1.append(a[2])
			list3_2.append(a[4])
			list4_1.append(a[5])
			list4_2.append(a[7])

		elif(space==4):
			#print("yes")
			a = str(lines1[l])
			a = a.split(" ")
			#print(a)
			list1.append(a[0])
			list2.append(a[1])
			list3.append(a[2])
			list4.append(a[3])
			list5.append(a[4])

		elif(space==6):
			#print("yes")
			a = str(lines1[l])
			a = a.split(" ")
			#print(a)
			list1.append(a[0])
			list2.append(a[1])
			list5.append(a[6])
			if(a[3]==':'):
				list3_11.append(a[2])
				list3_12.append(a[4])
				list4_21.append(a[5])
			elif(a[4]==':'):
				list3_21.append(a[2])
				list4_11.append(a[3])
				list4_12.append(a[5])


			
	with open('source_ip.txt','w') as fa2:
		for qw in range(0,len(list1)):
			ss=str(list1[qw][1:])
			fa2.write(ss)
			fa2.write("\n") 
	with open('dest_ip.txt','w') as f3:
		for qw in range(0,len(list2)):
			ss=str(list2[qw])
			f3.write(ss)
			f3.write("\n")
	with open('protocol.txt','w') as f4:
		for qw in range(0,len(list5)):
			ss=str(list5[qw][:-1])
			f4.write(ss)
			f4.write("\n")
	with open('source_port.txt','w') as f5:
		for qw in range(0,len(list3_1)):
			ss=str(list3_1[qw])+':'+str(list3_2[qw])
			f5.write(ss)
			f5.write("\n")
		for qw in range(0,len(list3)):
			aa=str(list3[qw])
			f5.write(aa)
			f5.write("\n")
		for qw in range(0,len(list3_11)):
			sa=str(list3_11[qw])+':'+str(list3_12[qw])
			f5.write(sa)
			f5.write("\n")
		for qw in range(0,len(list3_21)):
			sas=str(list3_21[qw])
			f5.write(sas)
			f5.write("\n")


	with open('dest_port.txt','w') as f6:
		for qw in range(0,len(list4_1)):
			ss=str(list4_1[qw])+':'+str(list4_2[qw])
			f6.write(ss)
			f6.write("\n")
		for qw in range(0,len(list4)):
			aa=str(list4[qw])
			f6.write(aa)
			f6.write("\n")
		for qw in range(0,len(list4_11)):
			sa=str(list4_11[qw])+':'+str(list4_12[qw])
			f6.write(sa)
			f6.write("\n")
		for qw in range(0,len(list4_21)):
			sas=str(list4_21[qw])
			f6.write(sas)
			f6.write("\n")
	with open('source_ip.txt','r') as fss2:
		lin2=fss2.readlines()
		for i in lin2:
			if i not in dis_sip:
				dis_sip.append(i)
		#print(dis_sip)
		sip_prefix=[]
		ss=[]
		with open('modify_source_ip.txt','w') as f2:
			for i in range(0,len(lin2)):
				kk=lin2[i].find('/')
				if(kk!=(-1)):
					ss= lin2[i].split("/")
					f=int(ipaddress.IPv4Address(ss[0]))
					f='{:032b}'.format(f)
					d=str(f)
					f2.write(d)
					#f2.write("..")
					#f2.write(ss[1])
					sip_prefix.append(ss[1]);
					f2.write("\n") 
				else:
					ss= lin2[i]
					f=int(ipaddress.IPv4Address(ss))
					f='{:032b}'.format(f)
					d=str(f)

					d=str(f)
					f2.write(d)

					f2.write(f)
					#f2.write("\n")
					sip_prefix.append('32')

		print("Number of distinct source_ip_address===",len(dis_sip))
		print("\n")
	with open('dest_ip.txt','r') as fss3:
		lin3=fss3.readlines()
		for i in lin3:
			if i not in dis_dip:
				dis_dip.append(i)
		#print(dis_dip)
		dip_prefix=[]
		ss=[]
		with open('modify_dest_ip.txt','w') as f32:
			for i in range(0,len(lin3)):
				kk=lin3[i].find('/')
				if(kk!=(-1)):
					ss= lin3[i].split("/")
					f=int(ipaddress.IPv4Address(ss[0]))
					f='{:032b}'.format(f)
					d=str(f)
					f32.write(d)
					#f2.write("..")
					#f2.write(ss[1])
					dip_prefix.append(ss[1]);
					f32.write("\n") 
				else:
					ss= lin3[i]
					f=int(ipaddress.IPv4Address(ss))
					f='{:032b}'.format(f)
					d=str(f)

					d=str(f)
					f32.write(d)

					f32.write(f)
					#f2.write("\n")
					dip_prefix.append('32')

		print("Number of distinct dest_ip_address===",len(dis_dip))
		print("\n")

	with open('source_port.txt','r') as fss4:
		lin4=fss4.readlines()
		for i in lin4:
			if i not in dis_sport:
				dis_sport.append(i)
		#print(dis_sport)
		print("Number of distinct source_port values===",len(dis_sport))
		print("\n")

	with open('dest_port.txt','r') as fss5:
		lin5=fss5.readlines()
		for i in lin5:
			if i not in dis_dport:
				dis_dport.append(i)
		#print(dis_dport)
		print("Number of distinct dest_port values===",len(dis_dport))
		print("\n")

	with open('protocol.txt','r') as fss6:
		lin6=fss6.readlines()
		for i in lin6:
			if i not in dis_protocol:
				dis_protocol.append(i)
		#print(dis_protocol)
		print("Number of distinct protocol values===",len(dis_protocol))
		print("\n")

	dr_sip=((len(dis_sip))/(len(lines1)))
	dr_dip=((len(dis_dip))/(len(lines1)))
	dr_sport=((len(dis_sport))/(len(lines1)))
	dr_dport=((len(dis_dport))/(len(lines1)))
	dr_protocol=((len(dis_protocol))/(len(lines1)))
	#print("\n")
	#print("Ratio for source_ip_address======= ",dr_sip)
	#print("\n\n")
	
	#print("Ratio for dest_ip_address======= ",dr_dip)
	#print("\n\n")
	
	#print("Ratio for source_port======= ",dr_sport)
	#print("\n\n")
	
	#print("Ratio for dest_port======= ",dr_dport)
	print("\n\n")

	#print("Ratio for protocol======= ",dr_protocol)
	
	
	values=[dr_sip,dr_dip,dr_sport,dr_dport,dr_protocol]
	
	values.sort(reverse=True)
	
	#print(values)
	#print(a)
	#print("\ndest_prefixs starts\n")
	#print(b)
	#for i in range(len(values)):

	#llp=0
	with open('acl1_5K.trace','r') as f_tr:
		tr_lines=f_tr.readlines()
		print(len(tr_lines))
	#the following code is used for the debug of the trace...mostly not required 
	#for l in range(0,len(tr_lines)):
		#space=0;
		#for k in range(0,len(tr_lines[l])):
			#if(tr_lines[l][k]=='	'):
				#space=space+1;
		#if(space==5):
			#llp=llp+1
	#print(llp)
	sip_trace=[]			#trace lists starts
	dip_trace=[]
	sport_trace=[]
	dport_trace=[]
	protocol_trace=[]
	ak1=[]
	ak2=[]
	ak3=[]
	ak4=[]
	ak11=[]
	ak12=[]
	ak13=[]
	ak14=[]
	for l in range(0,len(tr_lines)):
		ab = str(tr_lines[l])
		ab = ab.split(" ")
		lk=int(ab[0])
		f='{:032b}'.format(lk)
		sip_trace.append(f)
		hj=int(ab[1])
		h='{:032b}'.format(hj)
		dip_trace.append(h)
		
		sport_trace.append(ab[2])
		
		dport_trace.append(ab[3])
		protocol_trace.append(ab[4])
#	for l in range(0,len(lin2)):
	#	if(int(sip_prefix[l]) == 0):		#here taking the don't care cases into the list
#			cou_sip.append(l)
#	print(len(cou_sip))
	#for l in range(0,len(lin3)):
	#	if(int(dip_prefix[l]) == 0):
	#		cou_dip.append(l)
	#print(len(cou_dip))
	with open('modify_source_ip.txt','r') as f_sip:
		tr_sip=f_sip.readlines()
		#print(len(tr_sip))
	with open('modify_dest_ip.txt','r') as f_dip:
		tr_dip=f_dip.readlines()
		#print(len(tr_dip))
	with open('source_port.txt','r') as f_sport:
		tr_sport=f_sport.readlines()
		print(len(tr_sport))
	with open('dest_port.txt','r') as f_dport:
		tr_dport=f_dport.readlines()
		print(len(tr_dport))
	for i in range(0,len(sip_trace)):
		cou_sip=[]
		cou_dip=[]
		cou_sport=[]
		cou_dport=[]
		
		for yu in range(0,len(tr_sip)):
			ax=int(sip_prefix[yu])
			if(int(sip_prefix[yu]) == 0):
				cou_sip.append(yu)
			
			elif(sip_trace[i] == tr_sip[yu][0:ax]):
				cou_sip.append(yu)
		ak1.append(len(cou_sip))	
	#print(ak1)
		for xc in range(0,len(tr_dip)):
			if xc in cou_sip:
				bx=int(dip_prefix[xc])
				if(int(dip_prefix[xc]) == 0):
					cou_dip.append(xc)
				elif(dip_trace[i] == tr_dip[xc][0:bx]):
					cou_dip.append(xc)
		ak2.append(len(cou_dip))
	#print(ak2)
		for xz in range(0,len(tr_sport)):
			if xz in cou_dip:
				ss=tr_sport[xz].split(":")
				sk1=ss[0]
				#print(sk1)
				sk2=ss[1]
				#print(sk2)
				for ia in range(int(sk1),int(sk2)+1):
					if(int(sport_trace[i]) == ia):
						cou_sport.append(xz)
		ak3.append(len(cou_sport))
	#print(ak3)
		for xcv in range(0,len(tr_dport)):
			if xcv in cou_sport:
				ss=tr_dport[xcv].split(":")
				sk1=ss[0]
				sk2=ss[1]
				for iu in range(int(sk1),int(sk2)+1):
					if (int(dport_trace[i])== iu):
						cou_dport.append(xcv)
		ak4.append(len(cou_dport))
	#print(ak4)				
	for io in range(0,len(tr_sip)):
		ak1[io]=ak1[io]+ak2[io]+ak3[io]+ak4[io]
	print(ak1)
	sum_1=sum(ak1)
	print(sum_1)
	for i in range(0,len(sip_trace)):
		cou_dip=[]
		cou_sip=[]
		cou_sport=[]
		cou_dport=[]
		for yu in range(0,len(tr_sip)):
			ax=int(sip_prefix[yu])
			if(int(sip_prefix[yu]) == 0):
				cou_sip.append(yu)
			
			elif(sip_trace[i] == tr_sip[yu][0:ax]):
				cou_sip.append(yu)
		ak11.append(len(cou_sip))	

		for xc in range(0,len(tr_dip)):
			if xc in cou_sip:
				bx=int(dip_prefix[xc])
				if(int(dip_prefix[xc]) == 0):
					cou_dip.append(xc)
				elif(dip_trace[i] == tr_dip[xc][0:bx]):
					cou_dip.append(xc)
		ak12.append(len(cou_dip))
		for er in range(0,len(tr_dport)):
			if er in cou_dip:
				ss=tr_dport[er].split(":")
				sk1=ss[0]
				sk2=ss[1]
				for ij in range(int(sk1),int(sk2)+1):
					if(int(dport_trace[i]) == ij):
						cou_dport.append(er)
		ak13.append(len(cou_dport))
		for xz in range(0,len(tr_sport)):
			if xz in cou_dport:
				ss=tr_sport[xz].split(":")
				sk1=ss[0]
				#print(sk1)
				sk2=ss[1]
				#print(sk2)
				for ia in range(int(sk1),int(sk2)+1):
					if(int(sport_trace[i]) == ia):
						cou_sport.append(xz)
		ak14.append(len(cou_sport))
	for a in range(0,len(tr_sip)):
		ak11[a]=ak11[a]+ak12[a]+ak13[a]+ak14[a]
		ak1[a]=ak1[a]-ak11[a]
	print(ak1)
	sum_2=sum(ak1)
	print(sum_2)
	percent=(sum_2/sum_1)
	print(percent)
