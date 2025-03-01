#
# Copyright 2020-present Facebook. All Rights Reserved.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI += "file://rotate_logfile \
            file://rotate_cri_sel \
            file://rotate_console_log \
            file://rsyslog.service \
"

MTERM_LOG_FILES := "mTerm_wedge"

do_install_append() {
  dst="${D}/usr/local/fbpackages/rotate"
  install -m 755 ${WORKDIR}/rotate_logfile ${dst}/logfile
  install -m 755 ${WORKDIR}/rotate_cri_sel ${dst}/cri_sel
  install -m 755 ${WORKDIR}/rotate_console_log ${dst}/console_log
  install -m 644 ${WORKDIR}/rsyslog.service ${D}${systemd_unitdir}/system

}

FILES_${PN} += "/usr/local/fbpackages/rotate"
