# LISE2011: to cluster significant triangles looking for active site

# LISE2022: rewritten in Python in 2022

# open

import os
<<<<<<< HEAD
import sys
import re


=======

import re



>>>>>>> 2ce08ca8ceb3debb3fb28ce3d17f3569d01cd164
def make_dir(homedir):

    dir1 = os.path.join(homedir, "results")

    dir2 = os.path.join(homedir, "details")

    dir3 = os.path.join(homedir, "tmp")

    if not os.path.exists(homedir):

        os.mkdir(homedir)

    if not os.path.exists(dir1):

        os.mkdir(dir1)

    if not os.path.exists(dir2):

        os.mkdir(dir2)

    if not os.path.exists(dir3):

        os.mkdir(dir3)



#def transfer(h, case):

def ata(nm, aa,ele):

    at = ' '

    #print(nm[1], nm, ele, aa)

    if ele == 'C':

        if nm[2] == ' ':

            at = '0'  # atom type assignment2022# 0: C2P#

        elif nm[2] == 'A':

            at = '2'  # atom type assignment2022# 2: C3P#

        elif nm[2] == 'B':

            if aa == "SER" or aa == "THR":

                at = '2'  # atom type assignment2022# 2: C3P#

            else:

                at = '1'  # atom type assignment2022# 1: C3N#

        elif nm[2] == 'G':

            if aa == "VAL" or aa == "LEU" or aa == "ILE" or aa == "MET" or aa == "THR" or aa == "PRO" or aa == "GLU" or aa == "GLN" or aa == "ARG" or aa == "LYS":

                at = '1'  # atom type assignment2022# 1: C3N#

            elif aa == "ASP" or aa == "ASN":

                at = '0'  # atom type assignment2022# 0: C2P#

            elif aa == "PHE" or aa == "TYR" or aa == "TRP":

                at = '3'  # atom type assignment2022# 3: CRN#

            elif aa == "HIS":

                at = '3'  # atom type assignment2022# 4: CRP#

            else:#if aa == "VAL" or aa == "LEU" or aa == "ILE" or aa == "MET" or aa == "PRO" or aa == "GLU" or aa == "GLN" or aa == "ARG" or aa == "LYS":

                at = '?'  # atom type assignment2022# ?: C3N#

                input('weird atom type')

        elif nm[2] == 'D':

            if aa == "LEU" or aa == "ILE" or aa == "LYS":

                at = '1'  # atom type assignment2022# 1: C3N#

            elif aa == 'GLU' or aa == 'GLN':

                at = '0'  # atom type assignment2022# 0: C2P#

            elif aa == 'ARG' or aa == 'PRO':

                at = '2'  # atom type assignment2022# 2: C3P#

            elif aa == 'PHE' or aa == 'TYR':

                at = '3'  # atom type assignment2022# 3: CRN#

            elif aa == 'HIS':

                at = '3'  # atom type assignment2022# 4: CRP#

            elif aa == 'TRP':

                if nm[3] == '1':

                    at = '4'  # atom type assignment2022# 4: CRP#

                elif nm[3] == '2':

                    at = '3'  # atom type assignment2022# 3: CRN#

                else:

                    at = '?'  # atom type assignment2022# ?: C#

                    input('weird atom type')

            else:

                at = '?'  # atom type assignment2022# ?: C#

                input('weird atom type')

        elif nm[2] == 'E':

            if aa == 'MET':

                at = '1'  # atom type assignment2022# 1: C3N#

            elif aa == 'LYS':

                at = '2'  # atom type assignment2022# 2: C3P#

            elif aa == 'PHE' or aa == 'TYR':

                at = '3'  # atom type assignment2022# 3: CRN#

            elif aa == 'HIS':

                at = '3'  # atom type assignment2022# 4: CRP#

            elif aa == 'TRP':

                if nm[3] == '2':

                    at = '4'  # atom type assignment2022# 4: CRP#

                elif nm[3] == '3':

                    at = '3'  # atom type assignment2022# 3: CRN#

                else:

                    at = '?'  # atom type assignment2022# ?: C#

                    input('weird atom type')

            else:

                at = '?'  # atom type assignment2022# ?: C#

                input('weird atom type')

        elif nm[2] == 'Z':

            if aa == 'ARG':

                at = '2'  # atom type assignment2022# 2: C3P#

            elif aa == 'PHE' or aa == 'TRP':

                at = '3'  # atom type assignment2022# 3: CRN#

            elif aa == 'TYR':

                at = '4'  # atom type assignment2022# 4: CRP#

            else:

                at = '?'  # atom type assignment2022# ?: C#

        elif nm[2] == 'H':

            at = '3'  # atom type assignment2022# 3: CRN#

        else:

            at = '?'  # atom type assignment2022# ?: C#

    elif ele == 'N':

        if nm[2] == ' ':

            if aa == 'PRO':

                at = '6'  # atom type assignment2022# 14: no type/NLA#

            else:

                at = '8'  # atom type assignment2022# 8: NRD#

        elif nm[2] == 'H' or nm[2] == 'Z': #Arg or Lys

            at = '7'  # atom type assignment2022# 7: NLC#

        elif aa == 'ASN' or aa == 'GLN' or aa == 'TRP':

            at = '8'  # atom type assignment2022# 8(6?): NRD/NLB#

        elif aa == 'HIS': #or aa == 'TRP':

            at = '9'  # atom type assignment2022# 9: NRE#

        elif aa == 'ARG': #NE of ARG

            at = '6'  # atom type assignment2022# 6: NLA#

        else:

            at = '?'  # atom type assignment2022# ?: N#

            input('weird atom type')

    elif ele == 'O':

        if nm[2] == ' ':

            at = '10'  # atom type assignment2022# 10: O2A#

        elif nm[2] == 'G' or nm[2] == 'H': #SER, THR or TYR

            at = '11'  # atom type assignment2022# 11: O3B#

        elif aa == 'ASN' or aa == 'GLN':

            at = '10'  # atom type assignment2022# 10: O2A#

        elif aa == 'ASP' or aa == 'GLU':

            at = '12'  # atom type assignment2022# 12: OLC#

        elif nm[2] == 'X':

            at = '12'  # atom type assignment2022# 12: OLC#

        else:

            at = '?'  # atom type assignment2022# ?: N#

            input('weird atom type')

    elif ele == 'S':

        at = '13' #atom type assignment2022# 13: S3N#

    else:

        at = '?'  # atom type assignment2022# ?: ?#

        input('weird atom type')

    #print(at)

    return at



def process_pdb(h, case):

    m1 = "PDB/" + case + ".pdb"

    target = os.path.join(h, m1)

    print(target)

    f = open(target, 'r')

    inf = f.readlines()

    f.close()

    print(len(inf))

    r = {'C':'1.7', 'N':'1.55','O':'1.52','S':'1.8'}

    f0 = "tmp/" + case + "_pro4c1.pdb"

    f1 = "tmp/" + case + "_ipro.txt"

    f2 = "tmp/" + case + "_asa1.pdb"

    f3 = "tmp/" + case + "_ilig.txt"

    f4 = "result/" + case + "_top10.pdb"

    f5 = "details/" + case + "_top3.pdb"

    tf0 = os.path.join(h, f0)

    tf1 = os.path.join(h, f1)  # input

    tf2 = os.path.join(h, f2)  # input

    tf3 = os.path.join(h, f3)  # input

    tf4 = os.path.join(h, f4)  # output

    tf5 = os.path.join(h, f5)  # output

    pno = []  # atom no.

    pnm = []  # atom name

    presnm = []  # residue name

    pchain = []  # chain name

    presno = []  # residue no.

    px = []  # x coordinate

    py = []  # y coordinate

    pz = []  # z coordinate

    ptag = []

    ptail = []

    pele = [] #element

    pat = [] #atom type

    #palter = [] #alternative location

    lno = []  # atom no.

    lnm = []  # atom name

    lresnm = []  # residue name

    lchain = []  # chain name

    lresno = []  # residue no.

    lx = []  # x coordinate

    ly = []  # y coordinate

    lz = []  # z coordinate

    ltag = []

    ltail = []

    lele = [] #element

    #lat = [] #atom type

    np = 0  # nof pro atom

    nl = 0  # nof lig atom

    # write to the first intermediate file

    print(tf1)

    fo = open(tf1, 'w')  # writes to tmp/{pdb_id}_ipro.txt file

    fo1 = open(tf3,'w')  # writes to tmp/{pdb_id}_ilig.txt file

    for i in inf:

        a = re.match(r'(ATOM|HETATM)', i)

        if a and a.group() == 'ATOM':

            #if i[16] != ' ':

            #    print(a.string)

            if i[16] != ' ' and i[16] != 'A':

                continue

            # print(a.string)

            ptag.append(i[0:6]) #ATOM card/tag

            pno.append(int(i[6:11])) #atom number

            pnm.append(i[12:16]) #atom name

            #palter.append(l[16]) #alternative location

            presnm.append(i[17:20]) #residue/amino acid name

            pchain.append(i[21]) #chain name

            presno.append(int(i[22:26])) #residue number

            px.append(float(i[30:38]))

            py.append(float(i[38:46]))

            pz.append(float(i[46:54]))



            ptail.append(i[54:78])

            pele.append(i[77])

            pat.append(ata(pnm[np],presnm[np],pele[np])) #atom type assignment

            #print("%6s%5d %4s %3s %s%4d    %8.3f%8.3f%8.3f%24s" % (

            #    ptag[np], pno[np], pnm[np], presnm[np], pchain[np], presno[np], px[np], py[np], pz[np], ptail[np]))

            s = presnm[np]+" "+str(presno[np])+" "+ pnm[np]+" "+str(px[np])+" "+str(py[np])+" "+str(pz[np])+" "+r[pele[np]]+" "+pat[np] +'\n'

            fo.write(s)

            np+=1

        elif a and a.group() == 'HETATM':  # and i[17:20] == 'STL':

            # print(a.string)

            if i[17:20] == 'HOH':

                continue

            elif i[17:20] == ' CL' or i[17:20] == 'SO4':

                continue

            m = re.match('(ZN|MG|CA|FE|NA|MN| K|NI|CU|CO|CD|HG|PT|MO|AL)', i[76:78])

            if m:

                ptag.append(i[0:6])  # ATOM card/tag

                pno.append(int(i[6:11]))  # atom number

                pnm.append(i[12:16])  # atom name

                # palter.append(l[16]) #alternative location

                presnm.append(i[17:20])  # residue/amino acid name

                pchain.append(i[21])  # chain name

                presno.append(int(i[22:26]))  # residue number

                px.append(float(i[30:38]))

                py.append(float(i[38:46]))

                pz.append(float(i[46:54]))



                ptail.append(i[54:78])

                pele.append(i[77])

                pat.append(ata(pnm[np], presnm[np], pele[np]))  # atom type assignment

                # print("%6s%5d %4s %3s %s%4d    %8.3f%8.3f%8.3f%24s" % (

                s = presnm[np] + " " + str(presno[np]) + " " + pnm[np] + " " + str(px[np]) + " " + str(

                    py[np]) + " " + str(pz[np]) + " 1.4 5\n"

                fo.write(s)

                np+=1

                continue

            ltag.append(i[0:6])

            lno.append(int(i[6:11]))

            lnm.append(i[12:16])

            lresnm.append(i[17:20])

            lchain.append(i[21])

            lresno.append(int(i[22:26]))

            lx.append(float(i[30:38]))

            ly.append(float(i[38:46]))

            lz.append(float(i[46:54]))

            ltail.append(i[54:78])

            lele.append(i[76:78])

            s = lresnm[nl] + " " + str(lresno[nl]) + " " + lnm[nl] + " " + str(lx[nl]) + " " + str(

                ly[nl]) + " " + str(lz[nl]) + " " + '\n'  # atom type assignment2022# 5: MET#

            fo1.write(s)

            #print("%6s%5d %4s %3s %s%4d    %8.3f%8.3f%8.3f%24s" % (

            #    ltag[nl], lno[nl], lnm[nl], lresnm[nl], lchain[nl], lresno[nl], lx[nl], ly[nl], lz[nl], ltail[nl]))

            # fo.write("%6s%5d %4s %3s %s%4d    %8.3f%8.3f%8.3f%24s\n" % (

            # ltag[nl], lno[nl], lnm[nl], lresnm[nl], lchain[nl], lresno[nl], lx[nl], ly[nl], lz[nl], ltail[nl]))

            nl += 1

    # fo.write("TER\n")

    # fo.write("END\n")

    print(np, nl)
    fo.seek(0)
    s = "Number of pro atoms: " + str(np) + "\n"
    fo.write(s)
    fo.close()

    fo1.close()

def LISE():

    print("LISE:")

    # my($enrich_data, $enrich_mark, $tri_dbm, $thr_choose, $tohit, $serial, $loc,) = (0, 77, 'tri_dbm', '089', 0, '2011817', 'online');  # online#

    # my @ parameters;

    abr = {

        'GLY': 'G', 'ALA': 'A', 'SER': 'S', 'CYS': 'C', 'VAL': 'V', 'THR': 'T', 'LEU': 'L',

        'ILE': 'I', 'ASP': 'D', 'ASN': 'N', 'GLU': 'E', 'GLN': 'Q', 'MET': 'M', 'HIS': 'H',

        'PHE': 'F', 'LYS': 'K', 'ARG': 'R', 'TYR': 'Y', 'TRP': 'W', 'PRO': 'P', 'UNK': 'U',

    }  # aa 3 letter --> 1 letter

    homedir = os.getcwd()

    make_dir(homedir)

    case = '1a6w'  # case = input('Please input a pdb id: ')

    x = re.match('^\d\w{3}$', case)

    if not x:

        print("It's not a typical pdb ID")

    else:

        print(case)

        process_pdb(homedir, case)



LISE()
