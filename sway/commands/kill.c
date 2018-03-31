#include <wlr/util/log.h>
#include "log.h"
#include "sway/input/input-manager.h"
#include "sway/input/seat.h"
#include "sway/tree/view.h"
#include "sway/tree/container.h"
#include "sway/commands.h"

struct cmd_results *cmd_kill(int argc, char **argv) {
	struct sway_container *con =
		config->handler_context.current_container;

	switch (con->type) {
	case C_ROOT:
	case C_OUTPUT:
	case C_WORKSPACE:
		return cmd_results_new(CMD_INVALID, NULL,
				"Can only kill views and containers with this command");
		break;
	case C_CONTAINER:
		con = container_destroy(con);
		con = container_reap_empty(con);
		arrange_windows(con, -1, -1);
		break;
	case C_VIEW:
		view_close(con->sway_view);
		break;
	default:
		break;
	}

	return cmd_results_new(CMD_SUCCESS, NULL, NULL);
}
