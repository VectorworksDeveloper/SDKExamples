// Reuire style sheets, inlcuding the tailwindcss
import "./app.css"

// Import Vue and our app component
import { createApp } from 'vue'
import App from './App.vue'

// Vectorworks SDK 2025 will automatically provide dark mode support for your web view
// via this setup here
window.setVectorworksThemeCallback((isDark) => {
    document.body.setAttribute('data-color-scheme', isDark ? 'dark' : 'light');
});

/* pre Vectorworks SDK 2025 code uses custom getLocalStrings function in our integrator object
exampleIntegrator.getLocalStrings()
*/
//
// Vectorworks SDK 2025 we use IInitContext::AddReourceAccessFunction in our CPaletteJSProvider::OnInit
// then we can access any resources from the .vwr file
exampleIntegrator.getResource('Strings/html.vwstrings')
.then( (txt) =>
	{
		let arr = JSON.parse(txt);
		document.trans = (str) => {
			return arr[str] ?? str + '_LOCALIZE';
		}
	})
.catch( (err) => {
	console.error('Error obtaining localized strings from Vectorworks: ' +err);
	document.trans = (str) => { return str; }
})
.finally(() => {
	// Setup Vue call as we want to wait for Vectorworks communication to initialize below do render the page
	const app = createApp(App);
	app.config.globalProperties.trans = (str) => document.trans(str);
	app.mount('#app');
});


