
all::
	@ echo Need target: windows-build, windows-install; exit 1

ABI_LIST = 32-win 64-win 32-mks 64-mks

windows-build::
	for abi in $(ABI_LIST); do jam.rbx -sBUILD_ABI=$${abi} lib || break; done

windows-install::
	@ [ "$(SKCPP_TARGET_DIR)" != "" ] || (echo "Need parameter: SKCPP_TARGET_DIR"; exit 1)
	eval `yaml-env.rbx -c config/build.yaml -e` && sh install-stemkit-cpp .. $(SKCPP_TARGET_DIR)/stemkit-$${release} $(ABI_LIST)
