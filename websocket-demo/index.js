const http = require("http")
const httpServer = http.createServer((_request, _response) => {
	console.log("We have received a request");
})
httpServer.listen(8080, () => console.log("My server is listening on port 8080."))
