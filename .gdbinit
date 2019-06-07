## Hello World

python
import os, os.path

class OSUConnect(gdb.Command):
    def __init__(self):
        super(OSUConnect, self).__init__("osu-connect", gdb.COMMAND_SUPPORT, gdb.COMPLETE_NONE, True)

    def invoke(self, arg, from_tty):
        print "connecting"
        gdb.execute('set args --no-sandbox --single-process')
        gdb.execute('target extended-remote :10022')


def setup_gdb_chrome(path_chromium):
    tools_path = os.path.join(path_chromium, "src","tools","gdb") 
    sys.path.insert(1, tools_path)
    import gdb_chrome
    gdb.execute('source %s' % os.path.join(tools_path, 'viewg.gdb'))

def setup_source_path(path_chromium):
    source_path = os.path.join(path_chromium, "src") 
    gdb.execute('set sysroot %s' % os.path.join(os.getcwd(), "tools/gdb/sysroot/"))

if os.getcwd().endswith("os-universe"):
    print "Setting up chrome debugging env..."
    path_chromium = os.path.join(os.getcwd(), "third_party","chromium")
    gdb.execute("set env CHROMIUM_GDBINIT_SOURCED=1")
    setup_source_path(path_chromium)
    setup_gdb_chrome(path_chromium)
    setup_connect_cmd()
    OSUConnect()
    print "Ready!"
