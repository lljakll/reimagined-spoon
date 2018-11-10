import java.lang.reflect.Array;
public class Topic3Stack {
    private T[] stack; // Stack entity
    private int TopOfStack = 0; // pointer to top most unused element of stack
    
    public Topic3Stack( Class c ){ // Constructor initializes array to 10 elements
        stack = (T[]) Array.newInstance(c, 10); // This part was the most challenging to figure out. I wish there was a simpler way.
    }
    
    public Topic3Stack( Class c, int count ) { // Constructor initializes array to 'count' elements
        stack = (T[]) Array.newInstance(c, count); // This part was the most challenging to figure out. Initializing the array was dificult. I wish there was a simpler way. 
    }
    
    public int size(){
        return TopOfStack; // Top of Stack pointer represents the actual number of elements stored on the stack
    }
    
    public boolean isEmpty(){
        return TopOfStack == 0; // 0 elements on the stack
    }
    
    public void push(T value){
        // Increase the size of the stack array if we are at the current size limit
        if (TopOfStack >= stack.length){
            grow();
        }
        
        stack[TopOfStack] = value; // Store value on the stack
        TopOfStack++; // Increment top of stack
    }
    
    public T pop(){
        // Stack is empty return null
        if ( TopOfStack <= 0 ){
            return null;
        }
        
        T temp = stack[TopOfStack - 1];  // Create temp value to store top most element which is one below the top of the stack
        stack[TopOfStack - 1] = null; // Set the value of the top most element getting popped to null.
        TopOfStack--; //decrement top of stack
        return temp; // retrun the temp value stored eairler.
    }
    
    public T top(){
        // Stack is empty return null
        if ( TopOfStack <= 0 ){
            return null;
        }
        else { // Retrun top most element on the stack, it is one below the top of the stack.
            return stack[TopOfStack - 1];
        }
    }
    
    private void grow(){
        // Create a temp array ten elements larger than the current stack
        Object[] temp = new Object[TopOfStack + 10];
        
        // copy over the stack to the temp array
        System.arraycopy(stack, 0, temp, 0, stack.length);
        
        // make the stack variable point to the newly created array.
        stack = (T[]) temp;
    }
}