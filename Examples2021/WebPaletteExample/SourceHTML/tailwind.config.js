const defaultTheme = require('tailwindcss/defaultTheme');

module.exports = {
	content: ["./src/**/*.{html,js,vue}"],
	theme: {
		extend: {
			fontFamily: {
				sans: ['Nunito', ...defaultTheme.fontFamily.sans],
			}
		},
	},
	plugins: [
	],
	
//	// this part will include more of tailwind by default
//	// we do this only for the 'all' npm run scripts (see package.json)
//	...(process.env.npm_lifecycle_event == 'dev' || process.env.npm_lifecycle_event == 'watch') && {
//		safelist: [
//			{ 
//				pattern: /.*/,
//				variants: [
//					//"first",
//					//"last",
//					//"odd",
//					//"even",
//					//"visited",
//					//"checked",
//					//"empty",
//					//"read-only",
//					//"group-hover",
//					//"group-focus",
//					//"focus-within",
//					//"hover",
//					//"focus",
//					//"focus-visible",
//					//"active",
//					//"disabled",
//					],
//			},
//		],
//	},
}
