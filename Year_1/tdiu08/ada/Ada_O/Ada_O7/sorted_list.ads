-- sorted_list.ads --
-- hugho678: Samarbetat med carbj841, Carl Björlin, samma program

package Sorted_List is
   
   type List_Type is private;
   
   function Empty (List: in List_Type) return Boolean;
   
   procedure Insert (List: in out List_Type; Key: in Integer);
   
   procedure Put (List: in List_Type);
   
   function Member (List: in List_Type; Value: in Integer) return Boolean;
   
   procedure Remove (List: in out List_Type; Key  : in Integer);
   
   procedure Delete (List: in out List_Type);
   
   function Length (List: in List_Type) return Integer;
   
   No_Such_Element_Error: exception;
   
   
private
   
   type Pointer;
     
   type List_Type is access Pointer;
   
   type Pointer is
      record
	 Data: Integer;
	 Next: List_Type;
      end record;
   
end Sorted_List;
