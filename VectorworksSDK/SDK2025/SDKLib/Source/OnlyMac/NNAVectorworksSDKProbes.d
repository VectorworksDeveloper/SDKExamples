provider VectorworksSDK {
	probe log_string( char *);
	
	probe start_plugins_load();
	probe end_plugins_load();
	
	probe start_plugin_load();
	probe loading_plugin( char * );
	probe end_plugin_load();
};