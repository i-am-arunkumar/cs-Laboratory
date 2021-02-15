import re 

#ACTAGATCAGATCAATGATATCGATG

ini_str = input("Enter the Dna Sequence : ")
  
AGAT_count = len(re.findall('(?=AGAT)', ini_str)) 
AATG_count = len(re.findall('(?=AATG)', ini_str)) 
TATC_count = len(re.findall('(?=TATC)', ini_str)) 
  
print("AGAT  :  ", AGAT_count)
print("AATG  :  ", AATG_count)
print("TATC  :  ", TATC_count)
