public class MyThread extends Thread{
    @Override
    public void run(){
        for (int i = 1; i <= 5; i++) {
            System.out.println(Thread.currentThread().getName() + " printing: " + i);
            try {
                Thread.sleep(500);                
            } catch (InterruptedException e) {
                System.out.println("Thread interruped: " + e.getMessage());
            }
            
        }
    }
}