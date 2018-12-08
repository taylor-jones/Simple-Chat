.PHONY : build server client clean clean_server clean_client

# 
# Build
# 

build: server client
		
server:
		cd Server && $(MAKE)

client:
		cd Client && $(MAKE)


# 
# Clean
# 

clean: clean_server clean_client

clean_server:
		cd Server && $(MAKE) clean
	
clean_client:
		cd Client && $(MAKE) clean