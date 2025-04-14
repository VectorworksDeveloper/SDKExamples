<template>
	<h1 class="text-3xl font-bold underline text-red-800">
		{{this.trans('hello')}}
	</h1>
	<HelloWorld class="p-2" msg="An example of fethcing data from Vectorworks. does it?" />
</template>

<script>
import HelloWorld from './components/HelloWorld.vue'

export default {
	components: {
		HelloWorld,
	},
}
</script>
