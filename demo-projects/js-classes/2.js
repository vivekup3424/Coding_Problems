import path from "path"
import fspromises from "fs/promises"
console.log(path.resolve('wwwroot', 'static_files/png/', '../gif/image.gif'))
try {
	const filePath = path.resolve("./manifest.json")
	const data = await fspromises.readFile(filePath, "utf8")
	const dataObject = JSON.parse(data)
	const services = dataObject["services"]
	for (const [serviceName, serviceMetaData] of Object.entries(services)) {
		console.log(serviceName)
		console.log(serviceMetaData)
	}
} catch (err) {
	console.error(err)
}
