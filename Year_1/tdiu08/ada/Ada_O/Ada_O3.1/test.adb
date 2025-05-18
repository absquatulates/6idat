-- Ada_O3.1 --
-- hugho678: Samarbetat med carbj841, Carl Björlin, samma program

with Ada.Text_IO;                                 use Ada.Text_IO;
with Ada.Integer_Text_IO;                         use Ada.Integer_Text_IO;
with Ada.Float_Text_IO;                           use Ada.Float_Text_IO; 


procedure Test is
   
   -- DS1 --
   
   type DS1_Type is
      record
	 
	 W: Character;
	 P: String(1..4);
	 
      end record;
   
   -- DS2 --
   
   type DU_Type is
      record
	 
	 S: Float;
	 Z: String(1..4);
	 
      end record;
   
   type DS2_Type is
      record
	 
	 D, U: DU_Type;
	 
      end record;
   
   -- DS3 --
   
   type JB_Type is
      record
	 
	 Y: Character;
	 Q: Character;
	 
      end record;
   
   type O_Type is
      record
	 
	 T: Boolean;
	 L: Character;
	 
      end record;
   
   type DS3_Type is
      record
	 
	 J, B: JB_Type;
	 O: O_Type;
	 
      end record;
   
   -- Underprogram --
   
   -- DS1--
   
   procedure Get(DS1: out DS1_Type) is
      
      C: Character;
      
   begin 
      
      Get(DS1.W);
      Get(C);
      Get(DS1.P);
      
      
   end Get; 
   
   procedure Put(DS1: in DS1_Type) is
      
   begin
      
      Put(DS1.W);
      Put(" ");
      Put(DS1.P);
      
   end Put;  
   
   -- DS2 --    
   
   procedure Get (DU: out DU_Type) is
      
      C: Character;
      
   begin   
      
      Get(DU.S);
      Get(C);
      Get(DU.Z); 
      
   end Get;
   
   procedure Get(DS2: out DS2_Type) is
      
      
   begin 
      
      Get(DS2.D);
      Get(DS2.U);
      
   end Get;  
   
   procedure Put (DU: in DU_Type) is
      
   begin
      
      Put(DU.S, 0, 3, 0);
      Put(" ");
      Put(DU.Z);

   end Put;
   
   procedure Put(DS2: in DS2_Type) is
      
   begin
      
      Put(DS2.D);
      Put(" ");
      Put(DS2.U);
      
   end Put;    

   -- DS3 -- 
   
   procedure Get (JB: out JB_Type) is
      
      C: Character;
      
   begin
      
      Get(JB.Y);
      Get(C);
      Get(JB.Q);
      Get(C);
      
   end Get;
   
   procedure Get (O: out O_Type) is
      
      C: Character;
      TF: Character;
      
   begin
      
      Get(TF);
      if TF = 'T' then
	 O.T := True;
      elsif TF = 'F' then
	 O.T := False;
      end if;
      
      Get(C);
      Get(O.L);
      
   end Get;
   
   
   procedure Get (DS3: out DS3_Type) is
      
      
   begin
      
      Get(DS3.J);
      Get(DS3.B);
      Get(DS3.O);

   end Get;
   
   
   procedure Put (JB: in JB_Type) is
      
   begin
      
      Put(JB.Y);
      Put(" ");
      Put(JB.Q);
      Put(" ");
      
   end Put;
   
   procedure Put (O: in O_Type) is
      
   begin
      
      if O.T then
	 Put("True");
      else
	 Put("False");
      end if;
      Put(" ");
      Put(O.L);
      
   end Put;
   
   procedure Put (DS3: in DS3_Type) is
      
   begin
      
      Put(DS3.J);
      Put(DS3.B);
      Put(DS3.O);
      
   end Put;
   
   
   -- HUVUDPROGRAM --
   
   -- Huvudprogrammets deklarationer
   
   DS1: DS1_Type;
   DS2: DS2_Type;
   DS3: DS3_Type;
   
begin
   
   --DS1
   
   Put_Line("För DS1:");
   Put("Mata in datamängd: ");
   Get(DS1);
   Skip_Line;

   Put("Inmatad datamängd: ");
   Put(DS1);
   New_Line(2);
   
   
   -- DS2
   
   Put_Line("För DS2:");
   Put("Mata in datamängd: ");
   Get(DS2);
   Skip_Line;
   
   Put("Inmatad datamängd: ");
   Put(DS2);
   New_Line(2);
   
   
   -- DS3
   
   Put_Line("För DS3:");
   Put("Mata in datamängd: ");
   Get(DS3);
   
   Put("Inmatad datamängd: ");
   Put(DS3);
   New_Line;
   
   
end Test;   
