-- hugho678: Samarbetat med carbj841, Carl Björlin, samma program

with Ada.Text_IO;            use Ada.Text_IO;
with Ada.Integer_Text_IO;    use Ada.Integer_Text_IO;
with Ada.Float_Text_IO;      use Ada.Float_Text_IO;
  
procedure Test is 
   I: Integer;
   F: Float;
   C: Character;
   S: String(1..5);
		    
begin

   -- Test 1 
   Put("Skriv in ett heltal: ");
   Get(I);
   
   Put("Du skrev in talet: ");
   Put(I, Width=> 2);
   Skip_Line;
   New_Line(2);
   
   -- Test 2
   Put("Skriv in fem heltal: ");
   Get(I);
   Put("Du skrev in talen: ");
   Put(I, Width=> 1);
   Put(" ");
   Get(I);
   Put(I, Width=> 1);
   Put(" ");
   Get(I);
   Put(I, Width=> 1);
   Put(" ");
   Get(I);
   Put(I, Width=> 1);
   Put(" ");
   Get(I);
   Put(I, Width=> 1);
   Skip_Line;
   New_Line(2);
   
   -- Test 3
   Put("Skriv in ett flyttal: ");
   Get(F);
   
   Put("Du skrev in flyttalet: ");
   Put(F, Fore=> 0, Aft=> 3, Exp=> 0); 
   Skip_Line;
   New_Line(2);
   
   -- Test 4
   Put("Skriv in ett heltal och ett flyttal: ");
   Get(I);
   Get(F);
   
   Put("Du skrev in heltalet: ");
   Put(I, Width=> 9); 
   New_Line;
   Put("Du skrev in flyttalet:"); 
   Put(F, Fore=> 4, Aft=>4, Exp=> 0);
   Skip_Line;
   New_Line(2);
   
   -- Test 5
   Put("Skriv in ett tecken: ");
   Get(C);
   
   Put("Du skrev in tecknet: ");
   Put(C); 
   Skip_Line;
   New_Line(2);
   
   -- Test 6
   Put("Skriv in en sträng med 5 tecken: ");
   Get(S);
   
   Put("Du skrev in strängen: ");
   Put(S); 
   Skip_Line;
   New_Line(2);
   
   -- Test 7
   Put("Skriv in en sträng med 3 tecken: ");
   Get(S(1..3));
   
   Put("Du skrev in strängen: ");
   Put(S(1..3));
   Skip_Line;
   New_Line(2);
   
   -- Test 8
   Put("Skriv in ett heltal och en sträng med 5 tecken: ");
   Get(I);
   Get(C);  
   Get(S);
   
   Put("Du skrev in talet |"); 
   Put(I, 1);
   Put("| och strängen |"); 
   Put(S); 
   Put("|.");
   Skip_Line;
   New_Line(2);
   
   -- Test 9
   Put("Skriv in en sträng med 3 tecken och ett flyttal: ");
   Get(S(1..3)); 
   Get(F);
   
   Put("Du skrev in "); 
   Put('"');
   Put(F, Fore=> 2, Aft=>  3, Exp=> 0); 
   Put('"'); 
   Put(" och "); 
   Put('"'); 
   Put(S(1..3)); 
   Put('"'); 
   Put(".");
   Skip_Line;
   New_Line(2);
   
     -- Test 10
   Put("Skriv in en sträng som är maximalt 5 tecken: ");
   Get_Line(S,I);
   Put("Du skrev in strängen: ");
   if I<5 then
      Put_Line(S(1..I));
   else
      Put_Line(S(1..I));
      Skip_Line;
   end if;   
   New_Line;
   
   -- Test 11
   Put("Skriv in en sträng som är maximalt 5 tecken: ");
   Get_Line(S,I);
   Put("Du skrev in strängen: ");
   if I<5 then
      Put_Line(S(1..I));
   else
      Put_Line(S(1..I));
      Skip_Line;
   end if;   
      
      
end Test;
