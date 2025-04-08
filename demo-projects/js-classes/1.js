class Fruit {
	constructor(_name) {
		this.name = _name
	}
	getName() {
		return JSON.stringify(this.name)
	}
	getConstructor() {
		return JSON.stringify(this.constructor)
	}
	getConstructorName() {
		return JSON.stringify(this.constructor.name)
	}
}
class Apple extends Fruit {
	constructor() {
		super("orange")
	}
}
const apple = new Apple()
console.log(apple.getName())
console.log(apple.getConstructor())
console.log(apple.getConstructorName())
