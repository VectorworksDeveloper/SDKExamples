'use strict'
const { merge } = require('webpack-merge');
const common = require('./webpack.config.common.js');
const webpack = require('webpack');

module.exports = merge(common, {
	mode: 'development',
	plugins: [
		new webpack.DefinePlugin({
			"__VUE_OPTIONS_API__": true,
			"__VUE_PROD_DEVTOOLS__": true,
		}),
	]
});