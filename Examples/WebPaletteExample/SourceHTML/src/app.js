// Reuire style sheets, inlcuding the tailwindcss
import "./app.css"

// Import Vue and our app component
import { createApp } from 'vue'
import App from './App.vue'

// Vectorworks localized strings
exampleIntegrator.getLocalStrings().then( (txt) =>
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


