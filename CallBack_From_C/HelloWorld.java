class HelloWorld {
	private native void print();

	public static void main(String[] args) {

        HelloWorld hw = new HelloWorld();
	for(int i=0 ; i <5; i++){
	    try {
       	Thread.sleep(1000);
        	}catch(Exception e) {
        		e.printStackTrace();
        	}
	    hw.print();
	}
	
		
	try
	{
		Thread.join();
	}catch(
	Exception e)
	{
		e.printStackTrace();
	}
	}
	public  static void printNumber(int number) {
		System.out.println("This is java method print number:"+number );
	}

	static {
		System.loadLibrary("HelloWorld");
	}
}
