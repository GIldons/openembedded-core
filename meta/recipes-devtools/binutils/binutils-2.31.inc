LIC_FILES_CHKSUM="\
    file://COPYING;md5=59530bdf33659b29e73d4adb9f9f6552\
    file://COPYING.LIB;md5=9f604d8a4f8e74f4f5140845a21b6674\
    file://COPYING3;md5=d32239bcb673463ab874e80d47fae504\
    file://COPYING3.LIB;md5=6a6a8e020838b23406c81b19c1d46df6\
    file://gas/COPYING;md5=d32239bcb673463ab874e80d47fae504\
    file://include/COPYING;md5=59530bdf33659b29e73d4adb9f9f6552\
    file://include/COPYING3;md5=d32239bcb673463ab874e80d47fae504\
    file://libiberty/COPYING.LIB;md5=a916467b91076e631dd8edb7424769c7\
    file://bfd/COPYING;md5=d32239bcb673463ab874e80d47fae504\
    "

def binutils_branch_version(d):
    pvsplit = d.getVar('PV').split('.')
    return pvsplit[0] + "_" + pvsplit[1]

BINUPV = "${@binutils_branch_version(d)}"

UPSTREAM_CHECK_GITTAGREGEX = "binutils-(?P<pver>\d+_(\d_?)*)"

SRCREV ?= "4568e49ff799192fea4f66063fe13e2b871ec75a"
BINUTILS_GIT_URI ?= "git://sourceware.org/git/binutils-gdb.git;branch=binutils-${BINUPV}-branch;protocol=git"
SRC_URI = "\
     ${BINUTILS_GIT_URI} \
     file://0003-configure-widen-the-regexp-for-SH-architectures.patch \
     file://0004-Point-scripts-location-to-libdir.patch \
     file://0005-Only-generate-an-RPATH-entry-if-LD_RUN_PATH-is-not-e.patch \
     file://0006-Use-libtool-2.4.patch \
     file://0007-Add-the-armv5e-architecture-to-binutils.patch \
     file://0008-don-t-let-the-distro-compiler-point-to-the-wrong-ins.patch \
     file://0009-warn-for-uses-of-system-directories-when-cross-linki.patch \
     file://0010-Fix-rpath-in-libtool-when-sysroot-is-enabled.patch \
     file://0011-Change-default-emulation-for-mips64-linux.patch \
     file://0012-Add-support-for-Netlogic-XLP.patch \
     file://0013-fix-the-incorrect-assembling-for-ppc-wait-mnemonic.patch \
     file://0014-Detect-64-bit-MIPS-targets.patch \
     file://0015-sync-with-OE-libtool-changes.patch \
     file://0016-add-i386pep-emulation-for-x86_64.patch \
     file://0017-improve-check-for-input-file-matching-output-file.patch \
     file://0018-Refactored-location-where-GOT-information-is-collect.patch \
     file://0019-Improved-robustness.-Return-FALSE-in-case-of-NULL-po.patch \
     file://0020-Make-sure-global-symbol-is-not-an-indirect-or-warnin.patch \
     file://0021-PLT-information-was-still-being-generated-when-symbo.patch \
     file://clang-bfd-fix.patch \
     file://CVE-2018-17358.patch \
     file://CVE-2018-17360.patch \
     file://CVE-2018-18309.patch \
     file://CVE-2018-18605.patch \
     file://CVE-2018-18606.patch \
     file://CVE-2018-18607.patch \
"
S  = "${WORKDIR}/git"

do_configure_prepend () {
        rm -rf ${S}/gdb ${S}/libdecnumber ${S}/readline ${S}/sim
}
