#CopyRight : Magdy

-include makeConfig.mk

show:
	echo $(OBJ)


all:$(P_BIN_DIR)/$(Project_name).bin $(P_BIN_DIR)/$(Project_name).hex
	@echo "==============Bild is Done=============="

%.o: %.s
	$(CC)as.exe $(CFLAGS) $< -o $@

$(OBJDIR)/%.o: %.c
	$(CC)gcc.exe $(INCS) $(CFLAGS) -c $< -o $(OBJDIR)/$(@F)

$(P_BIN_DIR)/$(Project_name).elf: $(OBJECTS) 
	$(CC)ld.exe -T $(LDSCRIPT)/linkerscript.ld $(LIBS) $(OBJ) -o $@ -Map=$(BINDIR)/map_file.map
	cp $(P_BIN_DIR)/$(Project_name).elf $(P_BIN_DIR)/$(Project_name).axf
	@echo "========= Binary Out Done ========="

$(P_BIN_DIR)/$(Project_name).bin: $(P_BIN_DIR)/$(Project_name).elf
	@$(CC)objcopy.exe -O binary $< $@
	@echo "========= Binary Out Done ========="
	
$(P_BIN_DIR)/$(Project_name).hex: $(P_BIN_DIR)/$(Project_name).elf
	@$(CC)objcopy.exe -O ihex $< $@
	@echo "========= Hex Out Done ========="

clean_all:
	rm -rf $(OBJDIR)/*.o $(BINDIR)/*.elf $(BINDIR)/*.bin $(BINDIR)/*.map $(BINDIR)/*.hex $(BINDIR)/*.axf *.o
	@echo "========= Cleaned Everything ========="
clean:
	rm -rf $(BINDIR)/*.elf $(BINDIR)/*.bin
	@echo "========= Cleaned .elf and .bin ========="