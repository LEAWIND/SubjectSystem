import os

SOURCE_DIR = "src"

SRC_EXT = {
    "python": ('py', ),
    "C": ('c', 'h'),
}


def printR(s, baseIndent=0):
    n0 = 0
    s0 = 0
    for k in s:
        n1 = 0
        s1 = 0
        for ext in s[k]:
            n1 += s[k][ext]['lines']
            s1 += s[k][ext]['chars']
        n0 += n1
        s0 += s1
        print(f"  {k}: {n0} lines, {s0} chars")
    print(f"Totally {n0} lines, {s0} chars")


def main():
    s = {}
    for tn in SRC_EXT:
        s[tn] = {}
        for tn2 in SRC_EXT[tn]:
            s[tn][tn2] = {
                'lines': 0,
                'chars': 0,
            }

    for dad, dirs, files in os.walk(SOURCE_DIR):
        for fname in files:
            fext = os.path.splitext(fname)[-1].lower()[1:]
            ftype = None
            for ft in SRC_EXT:
                if fext in SRC_EXT[ft]:
                    ftype = ft
                    break
            if ftype == None:
                continue
            with open(os.path.join(dad, fname), "r", encoding="utf-8") as file:
                tp = file.read()
                s[ftype][fext]['lines'] += len(tp.split('\n'))
                s[ftype][fext]['chars'] += len(tp)

    printR(s)


if __name__ == '__main__':
    main()
