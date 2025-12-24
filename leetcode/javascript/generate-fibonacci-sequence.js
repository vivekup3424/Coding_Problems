/**
 * @return {Generator<number>}
 */

var fibGenerator = function*(){
   let [a,b] = [0,1]
   while(true){
    yield a;
    [a,b] = [b,a+b];
   }

}