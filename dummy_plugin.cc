/* Plugin for testing dumpfile.c.  */

#include "gcc-plugin.h"
#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tree.h"
#include "tree-pass.h"
#include "intl.h"
#include "plugin-version.h"
#include "diagnostic.h"
#include "context.h"
#include "optinfo.h"
#include "gimple.h"
#include "gimple-iterator.h"
#include "cgraph.h"

int plugin_is_GPL_compatible;

const pass_data pass_data_dummy_plugin =
{
  GIMPLE_PASS, /* type */
  "dummy_plugin", /* name */
  OPTGROUP_LOOP, /* optinfo_flags */
  TV_NONE, /* tv_id */
  PROP_ssa, /* properties_required */
  0, /* properties_provided */
  0, /* properties_destroyed */
  0, /* todo_flags_start */
  0, /* todo_flags_finish */
};

class pass_dummy_plugin : public gimple_opt_pass
{
public:
  pass_dummy_plugin (gcc::context *ctxt)
    : gimple_opt_pass (pass_data_dummy_plugin, ctxt)
  {}

  /* opt_pass methods: */
  bool gate (function *) { return true; }
  virtual unsigned int execute (function *);

};

unsigned int
pass_dummy_plugin::execute (function *fun)
{
  return 0;
}

static gimple_opt_pass *
make_pass_dummy_plugin (gcc::context *ctxt)
{
  return new pass_dummy_plugin (ctxt);
}

int
plugin_init (struct plugin_name_args *plugin_info,
	     struct plugin_gcc_version *version)
{
  struct register_pass_info pass_info;
  const char *plugin_name = plugin_info->base_name;
  int argc = plugin_info->argc;
  struct plugin_argument *argv = plugin_info->argv;

  if (!plugin_default_version_check (version, &gcc_version))
    return 1;

  pass_info.pass = make_pass_dummy_plugin (g);
  pass_info.reference_pass_name = "ssa";
  pass_info.ref_pass_instance_number = 1;
  pass_info.pos_op = PASS_POS_INSERT_AFTER;
  register_callback (plugin_name, PLUGIN_PASS_MANAGER_SETUP, NULL,
		     &pass_info);

  return 0;
}
