import java.io.*;

class Word{
	private String word;
	private int quant;
	
	// Constructor
	public Word(String word){
		this.word = word;
		quant = 1;
	}
	
	// Accessors
	public int getCount(){
		return quant;
	}
	
	public String getWord(){
		return word;
	}
		
	public boolean isWord(String word){
		return word.equals(this.word);
	}
	
	public boolean isWordIgnoreCase(String word){
		return word.equalsIgnoreCase(this.word);
	}

// needs altering to do output file	
	public void print(){
		System.out.println(word+"\t"+quant);
	}
	
	public static int FindWord(Word[] list, String word, int n){
		int i=0;
		while(((word.equals(list[i].getWord()) != true) || i>n)){
			i++;
		}
		if(!(word.equals(list[i].getWord())))
			i=-1;
		return i;
	}
	
	// Mutator
	public void addOne(){
		quant += 1;
	}
}

class WordTest{
	public static void main(String[] args)throws IOException{
		BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
		String line=null;
		String word=null;
		Word[] words = new Word[10];		// Array of Word objects
		int count=0;
		int i=0;
		
		for(i=0;i<10;i++){
			System.out.print("Enter word #"+(i+1)+" : ");	// Prompt
			System.out.flush();								// Force print with no new line for curser to be at the end of the prompt.
			line = stdin.readLine();						// Read
			words[i] = new Word(line);
		}
		
		for(i=0;i<10;i++)
			words[i].print();
			
		System.out.println(words[1].getWord()+" and "+words[2].getWord()+" are the same word: "+words[2].isWord(words[1].getWord()));
		
		for(i=0;i<5;i++)
			words[1].addOne();
			
		System.out.println(words[1].getWord()+"\t"+words[1].getCount());
		
		i=10;
		int n = Word.FindWord(words,words[3].getWord(),i);
		System.out.println("The word is at location: "+n);
	}
}