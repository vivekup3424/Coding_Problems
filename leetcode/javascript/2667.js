const createHelloWorld = () => {
  return (...args) => {
    return "Hello, World";
  };
};

console.log(createHelloWorld()());
