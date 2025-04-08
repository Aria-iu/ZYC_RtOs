$(foreach config,$(filter CONFIG_%, $(.VARIABLES)), $(eval undefine $(config)))
