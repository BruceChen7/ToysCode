# 获取当前的版本
REL=$(shell python -c 'import lightsockets; print lightsockets.__version__')

.PHONY: local_proxy remote_proxy


local_proxy: 
	@echo Preparing to run  local proxy release $(REL)
	python local.py

remote_proxy:
	@echo Preparing to run remote proxy release $(REL)
	python server.py

 