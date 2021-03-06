// SPDX-License-Identifier: GPL-2.0+
/* NetworkManager Applet -- allow user control over networking
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * (C) Copyright 2010 Red Hat, Inc.
 */

#ifndef APPLET_MOBILE_HELPERS_H
#define APPLET_MOBILE_HELPERS_H

#include <gtk/gtk.h>
#include <libsecret/secret.h>

#include "applet.h"
#include "nma-mobile-wizard.h"
#include "nma-mobile-providers.h"

enum {
	MB_STATE_UNKNOWN = 0,
	MB_STATE_IDLE,
	MB_STATE_HOME,
	MB_STATE_SEARCHING,
	MB_STATE_DENIED,
	MB_STATE_ROAMING
};

enum {
	MB_TECH_UNKNOWN = 0,
	MB_TECH_1XRTT,
	MB_TECH_EVDO,
	MB_TECH_GSM,
	MB_TECH_GPRS,
	MB_TECH_EDGE,
	MB_TECH_UMTS,
	MB_TECH_HSDPA,
	MB_TECH_HSUPA,
	MB_TECH_HSPA,
	MB_TECH_HSPA_PLUS,
	MB_TECH_LTE,
};

GdkPixbuf *mobile_helper_get_status_pixbuf (guint32 quality,
                                            gboolean quality_valid,
                                            guint32 state,
                                            guint32 access_tech,
                                            NMApplet *applet);

const char *mobile_helper_get_quality_icon_name (guint32 quality);
const char *mobile_helper_get_tech_icon_name (guint32 tech);

/********************************************************************/

gboolean   mobile_helper_wizard (NMDeviceModemCapabilities capabilities,
                                 AppletNewAutoConnectionCallback callback,
                                 gpointer callback_data);

/********************************************************************/

extern const SecretSchema mobile_secret_schema;

void mobile_helper_save_pin_in_keyring   (const char *devid,
                                          const char *simid,
                                          const char *pin);
void mobile_helper_delete_pin_in_keyring (const char *devid);

/********************************************************************/

typedef struct {
	SecretsRequest req;
	GtkWidget *dialog;
	GtkEntry *secret_entry;
	char *secret_name;
	NMDeviceModemCapabilities capability;
} MobileHelperSecretsInfo;

gboolean mobile_helper_get_secrets (NMDeviceModemCapabilities capabilities,
                                    SecretsRequest *req,
                                    GError **error);

/********************************************************************/

void mobile_helper_get_icon (NMDevice *device,
                             NMDeviceState state,
                             NMConnection *connection,
                             GdkPixbuf **out_pixbuf,
                             const char **out_icon_name,
                             char **tip,
                             NMApplet *applet,
                             guint32 mb_state,
                             guint32 mb_tech,
                             guint32 quality,
                             gboolean quality_valid);

/********************************************************************/

char *mobile_helper_parse_3gpp_operator_name (NMAMobileProvidersDatabase **mpd,
                                              const char *orig,
                                              const char *op_code);

char *mobile_helper_parse_3gpp2_operator_name (NMAMobileProvidersDatabase **mpd,
                                               guint32 sid);

#endif  /* APPLET_MOBILE_HELPERS_H */
