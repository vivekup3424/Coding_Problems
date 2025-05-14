const esbuild = require('esbuild');

async function build() {
    const source = `index.ts`
    const dest = `out.js`
    esbuild.build({
        entryPoints: [source],
        bundle: true,
        outfile: dest,
        platform: 'node',
        sourcemap: true,
        target: ['es2022'],
        minify: true,
        external: ["avsc", "realm", "thrift", "kafka-node", "moleculer", "shelljs", "@keus-automation/kiotp_utilities", "readline/promises"],
        define: { 'process.env.NODE_ENV': '""' }, // Environment variable definitions
        format: "cjs",
        tsconfig: 'tsconfig.json', // Path to your tsconfig.json file,
        minifyWhitespace: true
    })
}


(async () => {
    build()
})()