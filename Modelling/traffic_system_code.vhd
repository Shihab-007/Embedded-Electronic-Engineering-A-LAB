
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
entity Traffic is
	Port ( 
		Direction: in std_logic_vector (3 downto 0);
		slot: in std_logic
	      );
   -- N is "00"
   -- W is "01" 
   -- S is "10"
   -- E is "11"
end Traffic;
architecture behavior of Traffic is
      -- Declaration of type and signal
type t_state is (NW,NE,SE,SW);
signal state: t_state;
signal FirstBit: std_logic_vector (1 downto 0) := Direction(3) & Direction(2);
signal SecondBit: std_logic_vector (1 downto 0) := Direction(1) & Direction(0);
begin
 	Process (Direction) is
		begin
-- Begin of the process
		if (Direction /= "0000" and Direction /= "1111")   --Don't do anything if the dorection is Nort-North or East-East
		then 
			case State is
				when NW =>   
				      if (secondBit /= "01" and slot = '1') -- If the second bit of the direction is different from the second bit
				      then State <= SW; -- Go to the next state
                                      else State <= NW;
                                      -- Otherwise remain to the state
                                      end if;
                                      if (secondBit = "01") --If the second bit of the direction is the same as the second bit of the state.
                                      then report "Exit succesful"; -- Exit the state
                                      end if;
                                 when SW =>
                                      if (secondBit /= "10" and slot = '1') -- If the second bit of the direction is different from the second bit
                                      then State <= SE; -- Go to the next state
                                      else State <= SW; -- Otherwise remain to the state
                                      end if;
                                      if (secondBit = "10") --If the second bit of the direction is the same as the second bit of the state
                                      then report "Exit succesful"; -- Exit the state
                                      end if;
                                  when SE =>
                                      if (secondBit /= "11" and slot = '1') -- If the second bit of the direction is different from the second bit
                                      then State <= NE; -- Go to the next state
                                      else State <= SE; -- Otherwise remain to the state
                                      end if;
                                      if (secondBit = "11") -- If the second bit of the direction is the same as the second bit of the state
                                      then report "Exit succesful"; -- Exit the state
                                      end if;
                                  when NE =>
                                      if (secondBit /= "00" and slot = '1') -- If the second bit of the direction is different from the second bit
                                      then State <= NW; --  Go to the next state.
                                      else state <= NE; -- Otherwise remain to the state
                                      end if;
                                      if (secondBit = "00") -- If the second bit of the direction is the same as the second bit of the state
                                      then report "Exit succesful"; -- Exit the state
                                      end if;
                                      when others =>
                                      report "The state is not present";
				  end case;                            
                               end if;
                       end process;
                 end behavior;
