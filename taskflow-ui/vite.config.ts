import { sveltekit } from '@sveltejs/kit/vite';
import { defineConfig } from 'vite';
import tailwindcss from '@tailwindcss/vite';

export default defineConfig({
	plugins: [
		tailwindcss(),
		sveltekit(),
	  ],
	  ssr: {
		noExternal: ['@reduxjs/toolkit', 'immer']
	  },
	  server: {
		fs: {
		  allow: ["/keus-iot-platform/packages/"]
		}
	  }
});
