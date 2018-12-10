import os, tempfile, subprocess, unittest
from oeqa.sdk.case import OESDKTestCase
from oeqa.utils.subprocesstweak import errors_have_output
errors_have_output()

class BuildLzipTest(OESDKTestCase):
    def test_lzip(self):
        with tempfile.TemporaryDirectory(prefix="lzip", dir=self.tc.sdk_dir) as testdir:
            dl_dir = self.td.get('DL_DIR', None)
            tarball = self.fetch(testdir, dl_dir, "http://downloads.yoctoproject.org/mirror/sources/lzip-1.19.tar.gz")

            dirs = {}
            dirs["source"] = os.path.join(testdir, "lzip-1.19")
            dirs["build"] = os.path.join(testdir, "build")
            dirs["install"] = os.path.join(testdir, "install")

            subprocess.check_output(["tar", "xf", tarball, "-C", testdir])
            self.assertTrue(os.path.isdir(dirs["source"]))
            os.makedirs(dirs["build"])

            self._run("cd {build} && {source}/configure --srcdir {source} $CONFIGURE_FLAGS".format(**dirs))
            self._run("cd {build} && make -j".format(**dirs))
            self._run("cd {build} && make install DESTDIR={install}".format(**dirs))

            self.check_elf(os.path.join(dirs["install"], "usr", "local", "bin", "lzip"))
