# vi: set ft=python :

class GenRR2:
    def __init__(self, binpath, rr2path, payloadpath):
        self._binpath=binpath
        self._rr2path=rr2path
        self._payloadpath=payloadpath

    def gen_payload(self, stream):
        try:
            with open(self._payloadpath,"wb") as f:
                f.write(stream)
        except Exception as e:
            print e
    
    def gen_rr2(self):
        try: 
            with open(self._rr2path, "w") as f:
                f.write("'!/usr/bin/rarun2\nprogram=%s\nstdin=%s\n" % (self._binpath, self._payloadpath))
        except Exception as e:
            print e