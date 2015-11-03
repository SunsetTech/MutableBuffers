
import ycm_core

flags = [
    "-std=c99",
    "-ISource",
    
    "-x",
    "C"
]

def FlagsForFile(filename,**kwargs):
    return {
        'flags': flags,
        'do_cache': True
    }
