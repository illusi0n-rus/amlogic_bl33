#include <common.h>
#include <command.h>
#include <vpu.h>

#ifdef CONFIG_VPU_PRESET
static int do_vpu_enable(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	vpu_probe();
	return 0;
}

static int do_vpu_disable(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	vpu_remove();
	return 0;
}

static cmd_tbl_t cmd_vpu_sub[] = {
	U_BOOT_CMD_MKENT(probe, 2, 0, do_vpu_enable, "", ""),
	U_BOOT_CMD_MKENT(remove, 2, 0, do_vpu_disable, "", ""),
};


static int do_vpu(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	cmd_tbl_t *c;

	/* Strip off leading 'bmp' command argument */
	argc--;
	argv++;

	c = find_cmd_tbl(argv[0], &cmd_vpu_sub[0], ARRAY_SIZE(cmd_vpu_sub));

	if (c) {
		return	c->cmd(cmdtp, flag, argc, argv);
	} else {
		cmd_usage(cmdtp);
		return 1;
	}
}

U_BOOT_CMD(
	vpu,	8,	0,	do_vpu,
	"vpu sub-system",
	"vpu probe        - enable vpu layer\n"
	"vpu remove       - disable vpu layer\n"
);
#endif