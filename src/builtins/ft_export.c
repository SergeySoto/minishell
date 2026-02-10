#include "../../includes/minishell.h"
#include <unistd.h>
#include <stdio.h>

/*
    *Cosas a tener en cuenta para export:
    export 1VAR=value     # ❌ Error
    export 9_test=hello   # ❌ Error
    export =value         # ❌ Error
    export VAR            # ✅ OK (declara sin valor)
    export VAR=           # ✅ OK (valor vacío)
    export VAR=value      # ✅ OK (con valor)
    export _VAR=value     # ✅ OK (con valor)
    export "VAR"=value    # ✅ OK (las comillas se quitan)
*/