## Hello World

python
import os, os.path

class OSUConnect(gdb.Command):
    def __init__(self):
        super(OSUConnect, self).__init__("osu-connect", gdb.COMMAND_SUPPORT, gdb.COMPLETE_NONE, True)

    def invoke(self, arg, from_tty):
        print "connecting"
        gdb.execute('set args --no-sandbox --single-process --v=1 --ozone-platform=gbm')
        gdb.execute('target extended-remote :10022')
        gdb.execute('set env EGL_PLATFORM=surfaceless')
        gdb.execute('set env EGL_LOG_LEVEL=debug')

def setup_gdb_chrome(path_chromium):
    tools_path = os.path.join(path_chromium, "src","tools","gdb") 
    sys.path.insert(1, tools_path)
    import gdb_chrome
    gdb.execute('source %s' % os.path.join(tools_path, 'viewg.gdb'))

def setup_source_path(path_chromium):
    sysroot = os.path.join(os.getcwd(), "tools/gdb/sysroot/")
    gdb.execute('set sysroot %s' % sysroot)
    gdb.execute('set debug-file-directory %s' % os.path.join(sysroot, "mnt/sda"))

    # Let gdb know wher the source code is. Source code is relative path so we need to specify out/Osone
    gdb.execute('directory %s' % os.path.join(path_chromium, "src/out/Osone")) 

if os.getcwd().endswith("os-universe"):
    print "Setting up chrome debugging env..."
    path_chromium = os.path.join(os.getcwd(), "third_party","chromium")
    gdb.execute('set env CHROMIUM_GDBINIT_SOURCED=1')
    setup_source_path(path_chromium)
    setup_gdb_chrome(path_chromium)
    OSUConnect()
    print "Ready!"
