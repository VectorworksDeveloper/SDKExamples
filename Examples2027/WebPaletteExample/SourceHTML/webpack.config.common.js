'use strict'
const { VueLoaderPlugin } = require('vue-loader')
const common = require('./webpack.config.common.js');
const path = require('path');
const CopyWebpackPlugin = require('copy-webpack-plugin');

module.exports = {
	entry: [
	  	'./src/app.js',
	],
	output: {
		path: path.resolve(__dirname, '..', 'WebPaletteExample.vwr', 'html'),
		clean: true,
	},
	module: {
		rules: [
			{
				test: /\.vue$/,
				use: 'vue-loader'
			},
			{
				test: /\.css$/,
				include: path.resolve(__dirname, 'src'),
				use: ['style-loader', 'css-loader', 'postcss-loader'],
			},
		]
	},
	plugins: [
	  	new VueLoaderPlugin(),
		new CopyWebpackPlugin({
			patterns: [
				{ from: path.resolve(__dirname, 'src', 'index.html') }
			]
		})
	],
  }