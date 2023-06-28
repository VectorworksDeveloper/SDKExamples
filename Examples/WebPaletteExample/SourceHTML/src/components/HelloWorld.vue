<template>
	<div>
		<div>{{msg}}_suffix_extra</div>
		<button type="button" @click="onButtonClick" class="btn btn-blue">{{this.trans('fetch_button')}}</button>
		<div>
			<div
				v-for="item in arrItems" :key="item"
				class="my-2"
			>
				<span v-html="item"></span>
			</div>
		</div>
	</div>
</template>

<script>
export default {
	props: {
		msg: {
			default: ''
		},
	},

	data() {
		return {
			arrItems: [],
		}
	},

	methods: {
		addResult(txt) {
			let html = this.syntaxHighlight(txt);
			this.arrItems.push(html);
		},

		onButtonClick() {
			if (typeof exampleIntegrator === 'undefined')
			{
				this.addResult( 'Vectorworks is not the host of this page. Cannot fetch the data.' );
			}
			else
			{
				exampleIntegrator.getAllPlantData()
							.then( (result)=> {
								this.addResult( result );
							})
							.catch( () => {
								this.addResult( 'Error calling the Vectorworks function.' );
							})
			}
		},


		syntaxHighlight(json) {
			if (typeof json != 'string') {
				json = JSON.stringify(json, undefined, 2);
			}
			json = json.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
			return json.replace(/("(\\u[a-zA-Z0-9]{4}|\\[^u]|[^\\"])*"(\s*:)?|\b(true|false|null)\b|-?\d+(?:\.\d*)?(?:[eE][+\-]?\d+)?)/g, function (match) {
				var cls = 'number';
				if (/^"/.test(match)) {
					if (/:$/.test(match)) {
						cls = 'key';
					} else {
						cls = 'string';
					}
				} else if (/true|false/.test(match)) {
					cls = 'boolean';
				} else if (/null/.test(match)) {
					cls = 'null';
				}
				return '<span class="' + cls + '">' + match + '</span>';
			});
		},

	},

}
</script>

<style scoped>
	pre {outline: 1px solid #ccc; padding: 5px; margin: 5px; }
	.string { color: green; }
	.number { color: darkorange; }
	.boolean { color: blue; }
	.null { color: magenta; }
	.key { color: red; }
</style>