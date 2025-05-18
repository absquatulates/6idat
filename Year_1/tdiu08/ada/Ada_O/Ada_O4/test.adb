-- Ada.O4 --
-- hugho678: Samarbetat med carbj841, Carl Björlin, samma program

with Ada.Text_IO;         use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Test is
   
   Length_Error, Format_Error, Year_Error, Month_Error, Day_Error: exception;
   
   -- Datatyper --
   
   type Date_Type is
      record
	 Year:  Integer;
	 Month: Integer;
	 Day:   Integer;
      end record;
   
   ----------------------------------------------------------------------
   -- Underprogram fÃ¶r att skriva ut meny och hantera menyval         --
   --                                                                  --
   -- Underprogrammet skriver ut de menyval som finns tillgÃ¤ngliga.   --
   -- AnvÃ¤ndaren fÃ¥r mata in menyval tills denne matat in ett        --
   -- korrekt menyval.                                                 --
   ----------------------------------------------------------------------
   function Menu_Selection return Integer is
      
      N : Integer;
      
   begin
      Put_Line("1. Felkontrollerad heltalsinläsning");
      Put_Line("2. Längdkontrollerad stränginläsning");
      Put_Line("3. Felkontrollerad datuminläsning");
      Put_Line("4. Avsluta programmet");
      
      loop
	 Put("Mata in N: ");
	 Get(N);
	 exit when N in 1 .. 4;	 
	 Put_Line("Felaktigt N, mata in igen!");
      end loop;
      
      return N;
   end Menu_Selection;
   
   ----------------------------------------------------------------------
   -- Underprogram fÃ¶r menyval 1: "felhantering av heltalsinmatning"  --
   --                                                                  --
   -- Underprogrammet lÃ¥ter anvÃ¤ndaren mata in ett intervall angivet --
   -- med tvÃ¥ heltal Min och Max. Get_Safe anropas                    --
   -- sedan med detta intervall och skÃ¶ter felhanteringen av          --
   -- heltalsinlÃ¤sningen dÃ¤r anvÃ¤ndaren fÃ¥r mata in vÃ¤rden tills  --
   -- korrekt vÃ¤rde matas in.                                         --
   ----------------------------------------------------------------------
   procedure Get_Safe (Min, Max : in Integer;
		      Value : out Integer) is
      
   begin

      loop	 
	 
	 Put("Mata in värde (");
	 Put(Min, 0);
	 Put(" - ");
	 Put(Max, 0);
	 Put("): "); 
	 begin
	    Get(Value);
	    
	    if Value < Min then
	       Put("För litet värde. ");
	    elsif Value > Max then
	       Put("För stort värde. ");
	    end if;	    	
	    
	    exit when Value >= Min and Value <= Max;
	 exception      
	    when Data_Error =>
	       Put("Fel datatyp. ");
	       Skip_Line;
	 end;
	 
      end loop;

   end Get_Safe;   
   
   procedure Upg1 is
      
      Value, Min, Max : Integer;
      
   begin  
      
      Value := 0;
      
      Put("Mata in Min och Max: ");
      Get(Min);
      Get(Max);
      
      Get_Safe(Min, Max, Value);
      Skip_Line;
      
      Put("Du matade in heltalet ");
      Put(Value, Width => 0);
      Put_Line(".");      
   end Upg1;
   
   ------------------------------------------------------------------------
   -- Underprogram fÃ¶r menyval 2: "felhantering av strÃ¤nginmatning"    --
   --                                                                    --
   -- Underprogrammet skapar en strÃ¤ng som Ã¤r lika lÃ¥ng som parametern--
   -- Length. Underprogrammet skickar denna strÃ¤ng till                 --
   -- Get_Correct_String dÃ¤r felhanteringen av strÃ¤nginmatningen sker. --
   -- Om anvÃ¤ndaren matar in en fÃ¶r kort strÃ¤ng kommer                --
   -- Get_Correct_String kasta/resa undantag vilket inte ska             --
   -- fÃ¥ngas hÃ¤r utan i huvudprogrammet.                               --
   ------------------------------------------------------------------------
   procedure Get_Correct_String (S : out String) is
      
      C: Character;  
      
   begin
      
      loop
	 Get(C);
	 exit when C /= ' ';
      end loop;
      
      for I in S'Range loop
	 
	 if I /= S'Last and End_Of_Line then
	    raise Length_Error;
	 end if;
	 
	 S(I) := C;

	 if I = S'Last then
	    S(I) := C;
	 else
	    Get(C);
	 end if;
	 
      end loop; 
      
   end Get_Correct_String;   
   
   procedure Upg2 (Length : in Integer) is
      
      S : String(1 .. Length);
      
   begin      
      Put("Mata in en sträng med exakt ");
      Put(Length, Width => 0);
      Put(" tecken: ");
      
      Get_Correct_String(S);
      Skip_Line;
      
      Put_Line("Du matade in strängen " & S & ".");      
   end Upg2;
   
   ----------------------------------------------------------------------
   -- Underprogram fÃ¶r menyval 3: "felhantering av datuminmatning"    --
   --                                                                  --
   -- Underprogrammet anropar Get som i sin tur kommer lÃ¤sa in och    -- 
   -- kontrollera ett datums format och rimlighet. Om datumet Ã¤r      --
   -- felaktigt kommer Get kasta/resa undantag vilket detta            --
   -- underprogram ska fÃ¥nga, skriva ut felmeddelande fÃ¶r och sedan  --
   -- anropa Get igen.                                                 --
   ----------------------------------------------------------------------
   
   procedure Format (S : in String) is -- Kontrollerar om Format_Error ska kastas
      
   begin 
      
      for I in S'Range loop
	 if I=5 or I=8 then
	    if S(I) /= '-' then
	       raise Format_Error;
	    end if;
	 else
	    if S(I) not in '0'..'9' then
	       raise Format_Error;
	    end if;
	 end if;
      end loop;
      
   end Format;
   
   procedure Year_Month (Date : in Date_Type) is -- Kontrollerar om Year_Error eller Month_Error ska kastas
      
   begin 
      
      if Date.Year < 1532 or Date.Year > 9000 then
	 raise Year_Error;
      elsif Date.Month < 1 or Date.Month > 12 then
	 raise Month_Error;
      end if;     
      
   end Year_Month;
   
   procedure Februari (Date : in Date_Type) is -- Kontrollerar om Day_Error ska kastas vid månad Februari (Day.Month = 2)
      
      Skott: Boolean;  -- Boolean för Skottår
      
   begin
      
      if Date.Year mod 4 = 0 and Date.Year mod 100 /= 0 then
	 Skott := True;
      elsif Date.Year mod 400 = 0 then
	 Skott := True;
      else
	 Skott := False;
      end if;
      
      if Skott then
	 if Date.Day > 29 then
	    raise Day_Error;
	 end if;
      else
	 if Date.Day > 28 then
	    raise Day_Error;
	 end if;
      end if;
      
   end Februari;
   
   procedure Day (Date : in out Date_Type) is -- Kontrollerar om Day_Error ska kastas
      
   begin
      
      if Date.Day < 1 or Date.Day > 31 then
	 raise Day_Error;
      end if;

      if Date.Month = 4 or Date.Month = 6 or Date.Month = 9 or Date.Month = 11 then 
	 if Date.Day > 30 then
	    raise Day_Error;
	 end if;
      end if;
      
      if Date.Month = 2 then
      	 Februari(Date);
      end if;     
      
   end Day;
   
   procedure Get (Date : out Date_Type) is
      
      S : String(1..10);
      
   begin

      Get_Correct_String(S);
      Format(S);
      
      Date.Year  :=  Integer'Value(S(1..4));
      Date.Month :=  Integer'Value(S(6..7));
      Date.Day   :=  Integer'Value(S(9..10));
      
      Year_Month(Date);
      Day(Date);
      
   exception
      when Length_Error =>
	 raise Format_Error;
	 
   end Get;
   
   procedure Put (Date : in Date_Type) is
      
   begin
      
      Put(Date.Year, 0);
      Put("-");
      
      if Date.Month < 10 then
      	 Put(0, 0);
      end if;
      Put(Date.Month, 0);
      
      Put("-");
      
      if Date.Day < 10 then
      	 Put(0, 0);
      End if;
      Put(Date.Day, 0);

      
   end Put;   
   
   procedure Upg3 is
      
      Date : Date_Type;
      
   begin   
      
      loop
	 begin
	    Put("Mata in ett datum: ");
	    
	    Get(Date);
	    Skip_Line;
	    exit;	    
	    
	 exception
	    when Format_Error =>
	       Put("Felaktigt format! ");
	    when Year_Error =>
	       Put("Felaktigt år! ");
	    when Month_Error =>
	       Put("Felaktig månad! ");
	    when Day_Error =>
	       Put("Felaktig dag! ");
	 end;
	 
      end loop;
      
      Put("Du matade in ");
      Put(Date);
      New_Line;
            
   end Upg3; 
   
   -------------------------------------------------------------------------
   -- Huvudprogram                                                        --
   --                                                                     --
   -- Huvudprogrammet skriver ut och lÃ¥ter anvÃ¤ndaren vÃ¤lja val i en   --
   -- meny via underprogrammet Menu_Selection. Beroende pÃ¥ vilket        --
   -- menyval anvÃ¤ndaren valt kommer olika underprogram anropas.         --
   -- Observera att fÃ¶r menyval 2 kommer anvÃ¤ndaren fÃ¥ mata in lÃ¤ngden-- 
   -- av en strÃ¤ng vilket skickas vidare till underporgrammet Upg2 dÃ¤r  --
   -- strÃ¤ngen i sig skapas.                                             --
   -------------------------------------------------------------------------
   Choice, Length : Integer;
   
begin 
   loop
      Choice := Menu_Selection;
      
      if Choice = 1 then
	 Upg1;
	 
      elsif Choice = 2 then
      	 Put("Mata in en stränglängd: ");
      	 Get(Length);
      	 Skip_Line;
	 
      	 Upg2(Length);
	 
      elsif Choice = 3 then
	 Upg3;
	 
      else
	 Put_Line("Programmet avslutas.");
	 exit;
      end if;      
   end loop;
   
exception
   when Length_Error =>
      Put("För få inmatade tecken!");
      
end Test;
