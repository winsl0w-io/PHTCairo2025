Afl.print(`[*] Starting FRIDA config for PID: ${Process.id}`);


const cm = new CModule(`
  #include <string.h>
  #include <gum/gumdefs.h>

  #define BUF_LEN 256

  void afl_persistent_hook(GumCpuContext *regs, uint8_t *input_buf,
    uint32_t input_buf_len) {

    memcpy((void *)regs->rdi, input_buf, input_buf_len);
    regs->rsi = input_buf_len;
  }
  `,
  {
    memcpy: Module.getExportByName(null, "memcpy")
  }
);


const pStartAddr = DebugSymbol.fromName("fuzz_one_input").address;

Afl.setPersistentHook(cm.afl_persistent_hook);
Afl.setPersistentAddress(pStartAddr);
Afl.setEntryPoint(pStartAddr);
Afl.setInMemoryFuzzing();
Afl.setInstrumentLibraries();

Afl.done();
Afl.print("[*] All done!");
