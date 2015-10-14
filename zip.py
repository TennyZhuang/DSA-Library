import zipfile as zf
import glob, os, time, re

file_pat = re.compile(r'.+\.cpp|.+\h')

zip_file = zf.ZipFile(os.getcwd().split('/')[-1] + '.zip', 'w')

now = time.localtime(time.time())[:6]

files = list(filter(lambda s: file_pat.match(s), os.listdir()))

for file_name in files:
    info = zf.ZipInfo(file_name)
    info.date_time = now
    info.compress_type = zf.ZIP_DEFLATED
    f = open(file_name, 'r')
    zip_file.writestr(info, f.read())
    f.close()

zip_file.close()
